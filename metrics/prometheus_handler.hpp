#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

#include "experimental/expected.hpp"
#include "experimental/variant.hpp"

#include "metrics/counter.hpp"
#include "metrics/metric.hpp"
#include "metrics/observation.hpp"
#include "metrics/summary.hpp"

#include "prometheus/counter.h"
#include "prometheus/family.h"
#include "prometheus/registry.h"

#include "util/error.hpp"
#include "util/lru_map.hpp"

namespace Util = Dometer::Util;
using namespace std::experimental;

namespace prometheus {
    template<typename T>
    using FamilyRef = std::reference_wrapper<prometheus::Family<T>>;
    using AnyFamilyRef = variant<FamilyRef<Counter>, FamilyRef<Summary>>;
    using AnyMetricPtr = variant<Counter*, Summary*>;
}

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
            void cacheMetric(T* t, std::string);

            template<typename T, typename BuilderFn>
            expected<prometheus::FamilyRef<T>, Util::Error> getOrBuildMetricFamily(std::string, std::string, BuilderFn);

            void handleMetricEviction(prometheus::AnyMetricPtr, std::string);

            std::shared_ptr<prometheus::Registry> registry;
            Util::LRUMap<prometheus::AnyMetricPtr, std::string> metricCache;
            std::unordered_map<std::string, prometheus::AnyFamilyRef> metricFamilies;
    };
}

#include "metrics/prometheus_handler.ipp"
