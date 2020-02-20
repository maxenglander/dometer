#include <memory>

#include "dometer/metrics/handler/prometheus_pull_transport_options.hpp"
#include "dometer/metrics/handler/prometheus_transport_factory.hpp"
#include "dometer/metrics/handler/prometheus_transport_options.hpp"
#include "dometer/metrics/handler/prometheus_types.hpp"
#include "std/x/variant.hpp"

namespace dometer::metrics::handler {
    std::shared_ptr<prometheus::x::Transport> PrometheusTransportFactory::makeTransport(PrometheusTransportOptions options) {
        return std::x::visit(overloaded(
            [](PrometheusPullTransportOptions ppto) {
                return std::make_shared<prometheus::x::Transport>(
                    std::x::in_place_index<0>,
                    ppto.bindAddress,
                    ppto.metricsPath,
                    ppto.numThreads
                );
            }
        ), options);
    }
}
