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

namespace Util = Dometer::Util;
using namespace std::experimental;

namespace prometheus {
    template<typename T>
    using FamilyRef = std::reference_wrapper<prometheus::Family<T>>;
    using AnyFamilyRef = variant<FamilyRef<Counter>, FamilyRef<Summary>>;
}

namespace Dometer::Metrics {
    class PrometheusHandler {
        public:
            PrometheusHandler(std::shared_ptr<prometheus::Registry>);

            template<typename... L>
            void increment(const Counter<L...>&, Observation<uint64_t, L...>);

            template<typename... L>
            void observe(const Summary<L...>&, Observation<double, L...>);
        private:
            template<typename T, typename BuilderFn>
            expected<prometheus::FamilyRef<T>, Util::Error> getOrBuildMetricFamily(std::string, std::string, BuilderFn);

            std::unordered_map<std::string, prometheus::AnyFamilyRef> metricFamilies;

            std::unordered_map<std::string, std::reference_wrapper<prometheus::Family<prometheus::Counter>>> counters;
            std::unordered_map<std::string, std::reference_wrapper<prometheus::Family<prometheus::Summary>>> summaries;
            std::shared_ptr<prometheus::Registry> registry;
    };
}

#include "metrics/prometheus_handler.ipp"
