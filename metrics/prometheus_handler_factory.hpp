#pragma once

#include "metrics/prometheus_handler.hpp"
#include "metrics/prometheus_options.hpp"

namespace dometer::metrics {
    class PrometheusHandlerFactory {
        public:
            static PrometheusHandler makeHandler(PrometheusOptions options);
    };
}
