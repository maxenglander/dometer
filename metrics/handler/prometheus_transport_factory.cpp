#include <iostream>
#include <memory>
#include <string>

#include "metrics/handler/prometheus_pull_transport_options.hpp"
#include "metrics/handler/prometheus_transport_factory.hpp"
#include "metrics/handler/prometheus_transport_options.hpp"
#include "metrics/handler/prometheus_types.hpp"
#include "prometheus/exposer.h"
#include "x/variant.hpp"

namespace dometer::metrics::handler {
    std::shared_ptr<prometheus::x::Transport> PrometheusTransportFactory::makeTransport(PrometheusTransportOptions options) {
        return std::x::visit(overloaded(
            [](PrometheusPullTransportOptions ppto) {
                std::cout << "Creating pull transport bound to " << ppto.bindAddress << std::endl;
                return std::make_shared<prometheus::x::Transport>(
                    std::x::in_place_index<0>,
                    ppto.bindAddress
                );
            }
        ), options);
    }
}
