#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

#include "metrics/counter.hpp"
#include "metrics/metric.hpp"
#include "metrics/observation.hpp"
#include "metrics/summary.hpp"

#include "prometheus/counter.h"
#include "prometheus/family.h"
#include "prometheus/registry.h"

namespace Dometer::Metrics {
    class PrometheusHandler {
        public:
            PrometheusHandler(std::shared_ptr<prometheus::Registry>);

            template<typename... L>
            void increment(const Counter<L...>&, Observation<uint64_t, L...>);

            template<typename... L>
            void observe(const Summary<L...>&, Observation<double, L...>);
        private:
            std::unordered_map<std::string, std::reference_wrapper<prometheus::Family<prometheus::Counter>>> counters;
            std::unordered_map<std::string, std::reference_wrapper<prometheus::Family<prometheus::Summary>>> summaries;
            std::shared_ptr<prometheus::Registry> registry;
    };
}

#include "metrics/prometheus_handler.ipp"
