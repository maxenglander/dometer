#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

#include "experimental/expected.hpp"

#include "metrics/counter.hpp"
#include "metrics/metric.hpp"
#include "metrics/observation.hpp"
#include "metrics/prometheus_lru_map.hpp"
#include "metrics/prometheus_types.hpp"
#include "metrics/summary.hpp"

#include "prometheus/counter.h"
#include "prometheus/registry.h"
#include "prometheus/summary.h"

#include "util/error.hpp"
#include "util/lru_map.hpp"

namespace Util = Dometer::Util;
using namespace std::experimental;

namespace Dometer::Metrics {
    class PrometheusHandler {
        public:
            PrometheusHandler(std::shared_ptr<prometheus::Registry>);
            PrometheusHandler(std::shared_ptr<prometheus::Registry>, size_t);

            template<typename... L>
            void increment(const Counter<L...>&, Observation<uint64_t, L...>);

            template<typename... L>
            void observe(const Summary<L...>&, Observation<double, L...>);
        private:
            int foo();

            template<typename T>
            void cacheMetric(T* t, prometheus::ext::FamilyNameAndTimeSeriesCount);

            template<typename T, typename BuilderFn>
            expected<prometheus::ext::FamilyRef<T>, Util::Error> getOrBuildMetricFamily(std::string, std::string, BuilderFn);

            void handleMetricEviction(prometheus::ext::AnyMetricPtr, prometheus::ext::FamilyNameAndTimeSeriesCount);

            std::shared_ptr<prometheus::Registry> registry;
           // Util::LRUMap<prometheus::ext::AnyMetricPtr, prometheus::ext::FamilyNameAndTimeSeriesCount> metricCache;
            PrometheusLRUMap metricCache;
            std::unordered_map<std::string, prometheus::ext::AnyFamilyRef> metricFamilies;
    };
}

#include "metrics/prometheus_handler.ipp"
