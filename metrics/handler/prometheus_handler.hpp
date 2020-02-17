#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

#include "metrics/counter.hpp"
#include "metrics/handler/prometheus_lru_map.hpp"
#include "metrics/handler/prometheus_types.hpp"
#include "metrics/metric.hpp"
#include "metrics/observation.hpp"
#include "metrics/summary.hpp"
#include "prometheus/counter.h"
#include "prometheus/registry.h"
#include "prometheus/summary.h"
#include "util/error.hpp"
#include "util/lru_map.hpp"
#include "x/expected.hpp"

namespace util = dometer::util;
using namespace std::x;

namespace dometer::metrics::handler {
    class PrometheusHandler {
        public:
            PrometheusHandler();
            PrometheusHandler(std::shared_ptr<prometheus::Registry>);
            PrometheusHandler(size_t);
            PrometheusHandler(std::shared_ptr<prometheus::Registry>, size_t);

            template<typename... L>
            void increment(const dometer::metrics::Counter<L...>&, dometer::metrics::Observation<uint64_t, L...>);

            template<typename... L>
            void observe(const dometer::metrics::Summary<L...>&, dometer::metrics::Observation<double, L...>);
        private:
            template<typename T>
            void cacheMetric(T* t, prometheus::x::FamilyNameAndTimeSeriesCount);

            template<typename T, typename BuilderFn>
            expected<prometheus::x::FamilyRef<T>, util::Error> getOrBuildMetricFamily(std::string, std::string, BuilderFn);

            void handleMetricEviction(prometheus::x::AnyMetricPtr, prometheus::x::FamilyNameAndTimeSeriesCount);

            std::shared_ptr<prometheus::Registry> registry;
            PrometheusLRUMap metricCache;
            std::unordered_map<std::string, prometheus::x::AnyFamilyRef> metricFamilies;
    };
}

#include "metrics/handler/prometheus_handler.ipp"
