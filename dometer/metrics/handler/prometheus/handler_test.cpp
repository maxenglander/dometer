#include <memory>
#include <string>
#include <vector>

#include "dometer/metrics/example_histogram.hpp"
#include "dometer/metrics/handler/prometheus/handler.hpp"
#include "dometer/metrics/handler/prometheus/metric_cache.hpp"
#include "prometheus/registry.h"
#include "prometheus/x/types.hpp"
#include "gtest/gtest.h"

namespace dometer::metrics::handler::prometheus {
    class HandlerTest : public ::testing::Test {
        public:
            HandlerTest()
                : _max_time_series(10),
                  _registry(std::make_shared<::prometheus::Registry>()),
                  _handler(_max_time_series, _registry, std::vector<std::shared_ptr<::prometheus::x::Transport>>())
            {}
        protected:
            uint8_t _max_time_series;
            std::shared_ptr<::prometheus::Registry> _registry;
            handler _handler;
    };

    TEST_F(HandlerTest, WhenHistogramIsRecordedForFirstTime_ATimeSeriesIsAddedToRegistry) {
        EXPECT_EQ(_registry->Collect().size(), 0);

        std::map<std::string, std::string> labels({{"hello", "world"}});
        _handler.record(dometer::metrics::example_histogram::instance, labels, 1);

        EXPECT_EQ(_registry->Collect().size(), 1);

        auto metric_family = _registry->Collect()[0];
        EXPECT_EQ(metric_family.name, dometer::metrics::example_histogram::instance.name);
        EXPECT_EQ(metric_family.help, dometer::metrics::example_histogram::instance.description);

        EXPECT_EQ(metric_family.metric.size(), 1);
        auto metric = metric_family.metric[0];
        EXPECT_EQ(metric.histogram.bucket[1].cumulative_count, 1);
        EXPECT_EQ(metric.histogram.bucket[1].upper_bound, 10.0);

        EXPECT_EQ(metric.label.size(), 1);
        auto label = metric.label[0];
        EXPECT_EQ(label.name, "hello");
        EXPECT_EQ(label.value, "world");
    }

    TEST_F(HandlerTest, WhenHistogramIsRecordedForSecondTime_TheRegisteredTimeSeriesIsUpdated) {
        std::map<std::string, std::string> labels({{"hello", "world"}});
        _handler.record(dometer::metrics::example_histogram::instance, labels, 1);
        _handler.record(dometer::metrics::example_histogram::instance, labels, 2);

        EXPECT_EQ(_registry->Collect().size(), 1);
        auto metric_family = _registry->Collect()[0];
        EXPECT_EQ(metric_family.metric.size(), 1);
        auto metric = metric_family.metric[0];
        EXPECT_EQ(metric.histogram.bucket[1].cumulative_count, 2);
        EXPECT_EQ(metric.histogram.bucket[1].upper_bound, 10.0);
    }

    TEST_F(HandlerTest, WhenHistogramIsRecordedWithDifferentLabels_AdditionalTimeSeriesAreRegistered) {
        std::map<std::string, std::string> labels1({{"hello", "world"}});
        std::map<std::string, std::string> labels2({{"hello", "worf"}});

        _handler.record(dometer::metrics::example_histogram::instance, labels1, 1);
        _handler.record(dometer::metrics::example_histogram::instance, labels2, 2);

        EXPECT_EQ(_registry->Collect().size(), 1);
        auto metric_family = _registry->Collect()[0];
        EXPECT_EQ(metric_family.metric.size(), 2);
    }

    TEST_F(HandlerTest, WhenMaxTimeSeriesIsReached_LeastRecentlyUsedTimeSeriesAreEvicted) {
        for(int i = 0; i < 5; i++) {
            std::map<std::string, std::string> labels({{"index", std::to_string(i)}});
            _handler.record(dometer::metrics::example_histogram::instance, labels, 1);
        }

        EXPECT_EQ(_registry->Collect().size(), 1);
        auto metric_family = _registry->Collect()[0];
        EXPECT_EQ(metric_family.metric.size(), 2);
    }
}
