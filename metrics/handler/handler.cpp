#include "metrics/handler/handler.hpp"
#include "metrics/handler/prometheus_handler.hpp"

namespace dometer::metrics::handler {
    Handler::Handler(PrometheusHandler prometheusHandler) : handler(prometheusHandler) {}
}
