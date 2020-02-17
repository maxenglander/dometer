#pragma once

#include "metrics/handler/prometheus_handler.hpp"
#include "metrics/handler/prometheus_options.hpp"

namespace dometer::metrics::handler {
    class PrometheusHandlerFactory {
        public:
            static PrometheusHandler makeHandler(PrometheusOptions options);
    };
}
