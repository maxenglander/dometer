#include "metrics/prometheus_handler.hpp"
#include "metrics/prometheus_handler_factory.hpp"
#include "metrics/prometheus_options.hpp"

namespace dometer::metrics {
    PrometheusHandler PrometheusHandlerFactory::makeHandler(PrometheusOptions options) {
        PrometheusHandler handler(options.maxTimeSeries);
        return handler;
    }
}
