#include <functional>
#include <map>
#include <memory>
#include <string>

#include "dometer/metrics/handler/prometheus/metric_cache.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "prometheus/counter.h"
#include "prometheus/registry.h"
#include "prometheus/x/types.hpp"

using ::testing::_;
using ::testing::Eq;
using ::testing::MockFunction;
using ::testing::VariantWith;

namespace dometer::metrics::handler::prometheus {
    class MetricCacheTest : public ::testing::Test {
        public:
            MetricCacheTest()
                : _max_time_series(5),
                  _metric_cache(_max_time_series),
                  _registry(std::make_shared<::prometheus::Registry>())
            {}
        protected:
            uint8_t _max_time_series;
            metric_cache _metric_cache;
            std::shared_ptr<::prometheus::Registry> _registry;
    };

    TEST_F(MetricCacheTest, WhenANewMetricIsInserted_NotifiesInsertionListeners) {
        MockFunction<void(::prometheus::x::AnyMetricPtr, ::prometheus::x::FamilyNameAndTimeSeriesCount)> _insertion_listener;
        _metric_cache.on_insert(_insertion_listener.AsStdFunction());

        EXPECT_CALL(_insertion_listener, Call(_, _)).Times(0);

        auto& family = ::prometheus::BuildCounter().Name("hello_world").Help("Hello, world!").Register(*_registry);
        ::prometheus::x::FamilyNameAndTimeSeriesCount meta{"hello_world", 1};

        auto labels = std::map<std::string, std::string>();
        ::prometheus::Counter& counter = family.Add(labels);

        EXPECT_CALL(_insertion_listener, Call(VariantWith<::prometheus::Counter*>(&counter), Eq(meta))).Times(1);

        _metric_cache.put(&counter, meta);
    }

    TEST_F(MetricCacheTest, WhenMaxSizeIsReached_EvictsLeastRecentlyUsedMetric) {
        MockFunction<void(::prometheus::x::AnyMetricPtr, ::prometheus::x::FamilyNameAndTimeSeriesCount)> _eviction_listener;
        _metric_cache.on_evict(_eviction_listener.AsStdFunction());

        EXPECT_CALL(_eviction_listener, Call(_, _)).Times(0);

        auto& family = ::prometheus::BuildCounter().Name("hello_world").Help("Hello, world!").Register(*_registry);
        ::prometheus::x::FamilyNameAndTimeSeriesCount meta{"hello_world", 1};
        ::prometheus::Counter* first_counter = nullptr;

        for(int i = 0; i < _max_time_series + 1; i++) {
            auto labels = std::map<std::string, std::string>({{"index", std::to_string(i)}});
            ::prometheus::Counter& counter = family.Add(labels);
  
            if(i == 0)
                first_counter = &counter;
            if(i == _max_time_series)
                EXPECT_CALL(_eviction_listener, Call(VariantWith<::prometheus::Counter*>(first_counter), Eq(meta))).Times(1);
  
            _metric_cache.put(&counter, meta);
        }
    }

    TEST_F(MetricCacheTest, WhenMaxSizeIsReached_UsesTimeSeriesSizeToDecideEviction) {
        MockFunction<void(::prometheus::x::AnyMetricPtr, ::prometheus::x::FamilyNameAndTimeSeriesCount)> _eviction_listener;
        _metric_cache.on_evict(_eviction_listener.AsStdFunction());

        EXPECT_CALL(_eviction_listener, Call(_, _)).Times(0);

        auto& family = ::prometheus::BuildCounter().Name("hello_world").Help("Hello, world!").Register(*_registry);

        ::prometheus::Counter& first_counter = family.Add(std::map<std::string, std::string>({{"index", "1"}}));
        ::prometheus::x::FamilyNameAndTimeSeriesCount first_meta{"hello_world", _max_time_series};

        _metric_cache.put(&first_counter, first_meta);

        EXPECT_CALL(_eviction_listener, Call(VariantWith<::prometheus::Counter*>(&first_counter), Eq(first_meta))).Times(1);

        ::prometheus::Counter& second_counter = family.Add(std::map<std::string, std::string>({{"index", "2"}}));
        ::prometheus::x::FamilyNameAndTimeSeriesCount second_meta{"hello_world", 1};

        _metric_cache.put(&second_counter, first_meta);
    }
}
