#include "metrics/prometheus_handler.hpp"

#include "prometheus/registry.h"

namespace Dometer::Metrics {
    PrometheusHandler::PrometheusHandler(std::shared_ptr<prometheus::Registry> registry)
        :   registry(registry) {}
}
