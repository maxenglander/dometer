#pragma once

#include <unordered_map>

#include "metrics/handler.hpp"
#include "metrics/observation.hpp"

#include "prometheus/counter.h"
#include "prometheus/family.h"
#include "prometheus/registry.h"

namespace Util = Dometer::Util;

namespace Dometer::Metrics {
    class PrometheusHandler : public Handler {
        public:
            template<typename... T>
            void handle(Observation<T...>);
        private:
            template<typename... T>
            void handleCounter(Observation<T...>);

            std::unordered_map<std::string, prometheus::Family<prometheus::Counter>> counters;
            prometheus::Registry registry;
    };
}

#include "metrics/prometheus_handler.ipp"
