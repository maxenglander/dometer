#include <iostream>
#include <memory>
#include <vector>

#include "dometer/metrics/handler/prometheus_handler.hpp"
#include "dometer/metrics/handler/prometheus_handler_factory.hpp"
#include "dometer/metrics/handler/prometheus_options.hpp"
#include "dometer/metrics/handler/prometheus_transport_factory.hpp"
#include "prometheus/registry.h"
#include "std/x/variant.hpp"

namespace dometer::metrics::handler {
    PrometheusHandlerFactory::CollectableRegistrar::CollectableRegistrar(std::shared_ptr<prometheus::Registry> registry)
        :   registry(registry)
    {}

    template <class ConcreteTransport>
    void PrometheusHandlerFactory::CollectableRegistrar::operator()(ConcreteTransport& transport) {
        transport.RegisterCollectable(registry);
    }

    PrometheusHandler PrometheusHandlerFactory::makeHandler(PrometheusOptions options) {
        auto registry = std::make_shared<prometheus::Registry>();
        std::vector<std::shared_ptr<prometheus::x::Transport>> transports;
        CollectableRegistrar registrar(registry);

        for(auto it = options.transports.begin(); it < options.transports.end(); it++) {
            auto transport = PrometheusTransportFactory::makeTransport(*it);
            std::x::visit(registrar, *transport);
            transports.push_back(transport);
        }

        std::cout << "creating prometheus handler with max time series " << options.maxTimeSeries << std::endl;
        PrometheusHandler handler(options.maxTimeSeries, registry, transports);

        return handler;
    }
}
