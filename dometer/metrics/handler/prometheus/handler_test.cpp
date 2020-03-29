#include <memory>
#include <string>
#include <vector>

#include "dometer/metrics/counter.hpp"
#include "dometer/metrics/handler/prometheus/handler.hpp"
#include "dometer/metrics/handler/prometheus/metric_cache.hpp"
#include "prometheus/registry.h"
#include "prometheus/x/types.hpp"
#include "gtest/gtest.h"

namespace dometer::metrics::handler::prometheus {
    class HandlerTest : public ::testing::Test {
        public:
            HandlerTest()
                : _max_time_series(5),
                  _registry(std::make_shared<::prometheus::Registry>()),
                  _handler(_max_time_series, _registry, std::vector<std::shared_ptr<::prometheus::x::Transport>>())
            {}
        protected:
            uint8_t _max_time_series;
            std::shared_ptr<::prometheus::Registry> _registry;
            handler _handler;
    };

    TEST_F(HandlerTest, WhenCounterIsIncrementedForFirstTime_ATimeSeriesIsAddedToRegistry) {
        dometer::metrics::counter example_counter("example_counter", "An example counter.");

        EXPECT_EQ(_registry->Collect().size(), 0);

        std::map<std::string, std::string> labels({{"hello", "world"}});
        _handler.increment(example_counter, labels, 1);

        EXPECT_EQ(_registry->Collect().size(), 1);

        auto metric_family = _registry->Collect()[0];
        EXPECT_EQ(metric_family.name, example_counter.name);
        EXPECT_EQ(metric_family.help, example_counter.description);

        EXPECT_EQ(metric_family.metric.size(), 1);
        auto metric = metric_family.metric[0];
        EXPECT_EQ(metric.counter.value, 1);

        EXPECT_EQ(metric.label.size(), 1);
        auto label = metric.label[0];
        EXPECT_EQ(label.name, "hello");
        EXPECT_EQ(label.value, "world");
    }

    TEST_F(HandlerTest, WhenCounterIsIncrementedForSecondTime_TheRegisteredTimeSeriesIsUpdated) {
        dometer::metrics::counter example_counter("example_counter", "An example counter.");

        std::map<std::string, std::string> labels({{"hello", "world"}});
        _handler.increment(example_counter, labels, 1);
        _handler.increment(example_counter, labels, 2);

        EXPECT_EQ(_registry->Collect().size(), 1);
        auto metric_family = _registry->Collect()[0];
        EXPECT_EQ(metric_family.metric.size(), 1);
        auto metric = metric_family.metric[0];
        EXPECT_EQ(metric.counter.value, 3);
    }

    TEST_F(HandlerTest, WhenCounterIsIncrementedWithDifferentLabels_AdditionalTimeSeriesAreRegistered) {
        dometer::metrics::counter example_counter("example_counter", "An example counter.");

        std::map<std::string, std::string> labels1({{"hello", "world"}});
        std::map<std::string, std::string> labels2({{"hello", "worf"}});

        _handler.increment(example_counter, labels1, 1);
        _handler.increment(example_counter, labels2, 2);

        EXPECT_EQ(_registry->Collect().size(), 1);
        auto metric_family = _registry->Collect()[0];
        EXPECT_EQ(metric_family.metric.size(), 2);
    }

    TEST_F(HandlerTest, WhenMaxTimeSeriesIsReached_LeastRecentlyUsedTimeSeriesAreEvicted) {
        dometer::metrics::counter example_counter("example_counter", "An example counter.");

        for(int i = 0; i < _max_time_series + 3; i++) {
            std::map<std::string, std::string> labels({{"index", std::to_string(i)}});
            _handler.increment(example_counter, labels, 1);
        }

        EXPECT_EQ(_registry->Collect().size(), 1);
        auto metric_family = _registry->Collect()[0];
        EXPECT_EQ(metric_family.metric.size(), _max_time_series);
    }
}
