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

            template<typename... T> void handle(Observation<T...>);
        private:
            template<typename... T> void handleCounter(Observation<T...>);

            std::unordered_map<std::string, std::reference_wrapper<prometheus::Family<prometheus::Counter>>> counters;
            std::shared_ptr<prometheus::Registry> registry;
    };
}

#include "metrics/prometheus_handler.ipp"
