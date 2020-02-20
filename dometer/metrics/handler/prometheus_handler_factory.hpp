#pragma once

#include "dometer/metrics/handler/prometheus_handler.hpp"
#include "dometer/metrics/handler/prometheus_options.hpp"

namespace dometer::metrics::handler {
    class PrometheusHandlerFactory {
        public:
            static PrometheusHandler makeHandler(PrometheusOptions options);
    };
}
