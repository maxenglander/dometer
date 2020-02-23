#include "dometer/metrics/handler/handler.hpp"
#include "dometer/metrics/handler/prometheus_handler.hpp"

namespace dometer::metrics::handler {
    Handler::Handler(PrometheusHandler prometheusHandler) : concreteHandler(prometheusHandler) {}
}
