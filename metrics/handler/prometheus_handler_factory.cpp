#include <memory>
#include <vector>

#include "metrics/handler/prometheus_handler.hpp"
#include "metrics/handler/prometheus_handler_factory.hpp"
#include "metrics/handler/prometheus_options.hpp"
#include "metrics/handler/prometheus_transport_factory.hpp"
#include "prometheus/registry.h"
#include "x/variant.hpp"

namespace dometer::metrics::handler {
    PrometheusHandler PrometheusHandlerFactory::makeHandler(PrometheusOptions options) {
        auto registry = std::make_shared<prometheus::Registry>();
        std::vector<std::shared_ptr<prometheus::x::Transport>> transports;

        for(auto it = options.transports.begin(); it < options.transports.end(); it++) {
            auto transport = PrometheusTransportFactory::makeTransport(*it);
            std::x::visit([registry](auto& t) {
                t.RegisterCollectable(registry);
            }, *transport);
            transports.push_back(transport);
        }

        PrometheusHandler handler(options.maxTimeSeries, registry, transports);

        return handler;
    }
}
