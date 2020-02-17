#include "metrics/handler/prometheus_handler.hpp"
#include "metrics/handler/prometheus_handler_factory.hpp"
#include "metrics/handler/prometheus_options.hpp"

namespace dometer::metrics::handler {
    PrometheusHandler PrometheusHandlerFactory::makeHandler(PrometheusOptions options) {
        PrometheusHandler handler(options.maxTimeSeries);
        return handler;
    }
}
