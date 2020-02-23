#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include "dometer/metrics/counter.hpp"
#include "dometer/metrics/handler/prometheus_lru_map.hpp"
#include "dometer/metrics/metric.hpp"
#include "dometer/metrics/observation.hpp"
#include "dometer/metrics/summary.hpp"
#include "prometheus/counter.h"
#include "prometheus/registry.h"
#include "prometheus/summary.h"
#include "prometheus/x/types.hpp"
#include "dometer/util/error.hpp"
#include "dometer/util/lru_map.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;
using namespace std::x;

namespace dometer::metrics::handler {
    class PrometheusHandler {
        class CacheEvictor {
            public:
                CacheEvictor(std::unordered_map<std::string, prometheus::x::AnyFamilyRef>&,
                             prometheus::x::FamilyNameAndTimeSeriesCount&);
                template <class MetricPtr>
                void operator()(MetricPtr&&);
            private:
                std::unordered_map<std::string, prometheus::x::AnyFamilyRef>& metricFamilies;
                prometheus::x::FamilyNameAndTimeSeriesCount& meta;
        };

        public:
            PrometheusHandler(size_t,
                              std::shared_ptr<prometheus::Registry>,
                              std::vector<std::shared_ptr<prometheus::x::Transport>>);
            PrometheusHandler(const PrometheusHandler&);

            template<typename... L>
            void increment(const dometer::metrics::Counter<L...>&, dometer::metrics::Observation<uint64_t, L...>);

            template<typename... L>
            void observe(const dometer::metrics::Summary<L...>&, dometer::metrics::Observation<double, L...>);
        private:
            template<typename T>
            void cacheMetric(T* t, prometheus::x::FamilyNameAndTimeSeriesCount);

            template<typename T, typename BuilderFn>
            expected<prometheus::x::FamilyRef<T>, util::Error> getOrBuildMetricFamily(std::string, std::string, BuilderFn);

            PrometheusLRUMap metricCache;
            std::unordered_map<std::string, prometheus::x::AnyFamilyRef> metricFamilies;
            std::shared_ptr<prometheus::Registry> registry;
            std::vector<std::shared_ptr<prometheus::x::Transport>> transports;
    };
}

#include "dometer/metrics/handler/prometheus_handler.ipp"
