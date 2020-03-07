#include "dometer/metrics/handler/handler.hpp"
#include "dometer/metrics/handler/prometheus/handler.hpp"

namespace dometer::metrics::handler {
    handler::handler(dometer::metrics::handler::prometheus::handler prometheus_handler) : concrete_handler(prometheus_handler) {}
}
