#include <memory>
#include <vector>

#include "metrics/handler/prometheus_handler.hpp"
#include "metrics/handler/prometheus_handler_factory.hpp"
#include "metrics/handler/prometheus_options.hpp"
#include "metrics/handler/prometheus_transport_factory.hpp"
#include "prometheus/registry.h"

namespace dometer::metrics::handler {
    PrometheusHandler PrometheusHandlerFactory::makeHandler(PrometheusOptions options) {
        std::vector<std::shared_ptr<prometheus::x::Transport>> transports;

        for(auto it = options.transports.begin(); it < options.transports.end(); it++) {
            transports.push_back(PrometheusTransportFactory::makeTransport(*it));
        }

        auto registry = std::make_shared<prometheus::Registry>();

        PrometheusHandler handler(options.maxTimeSeries, registry, transports);

        return handler;
    }
}
