#include "dometer/metrics/handler/handler.hpp"
#include "dometer/metrics/handler/prometheus/handler.hpp"

namespace dometer::metrics::handler {
    Handler::Handler(dometer::metrics::handler::prometheus::Handler prometheusHandler) : concreteHandler(prometheusHandler) {}
}
