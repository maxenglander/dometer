#include "metrics/handler/prometheus_pull_transport_options.hpp"
#include "metrics/handler/prometheus_transport_factory.hpp"
#include "metrics/handler/prometheus_transport_options.hpp"
#include "metrics/handler/prometheus_types.hpp"
#include "x/variant.hpp"

namespace dometer::metrics::handler {
    prometheus::x::Transport PrometheusTransportFactory::makeTransport(PrometheusTransportOptions options) {
        std::x::visit(overloaded(
            [](PrometheusPullTransportOptions ppto) {
            }
        ), options);
    }
}
