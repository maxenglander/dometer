#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

#include "metrics/handler.hpp"
#include "metrics/observation.hpp"

#include "prometheus/counter.h"
#include "prometheus/family.h"
#include "prometheus/registry.h"

namespace Dometer::Metrics {
    class PrometheusHandler {
        public:
            PrometheusHandler(std::shared_ptr<prometheus::Registry>);

            template<typename... L> void handle(Observation<double, L...>);
            template<typename... L> void handle(Observation<uint64_t, L...>);
        private:
            template<typename... L> void handleCounter(Observation<uint64_t, L...>);
            template<typename... L> void handleSummary(Observation<double, L...>);

            std::unordered_map<std::string, std::reference_wrapper<prometheus::Family<prometheus::Counter>>> counters;
            std::unordered_map<std::string, std::reference_wrapper<prometheus::Family<prometheus::Summary>>> summaries;
            std::shared_ptr<prometheus::Registry> registry;
    };
}

#include "metrics/prometheus_handler.ipp"
