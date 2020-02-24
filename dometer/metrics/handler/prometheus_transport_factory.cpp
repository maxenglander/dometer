#include <memory>
#include <vector>

#include "dometer/metrics/handler/prometheus_pull_transport_options.hpp"
#include "dometer/metrics/handler/prometheus_transport_factory.hpp"
#include "dometer/metrics/handler/prometheus_transport_options.hpp"
#include "dometer/util/error.hpp"
#include "prometheus/x/types.hpp"
#include "std/x/expected.hpp"
#include "std/x/variant.hpp"

namespace util = dometer::util;

namespace dometer::metrics::handler {
    std::x::expected<std::shared_ptr<prometheus::x::Transport>, util::Error> PrometheusTransportFactory::makeTransport(
            PrometheusTransportOptions options) {
        try {
            return std::x::visit(std::x::overloaded(
                [](PrometheusPullTransportOptions ppto) {
                    return std::make_shared<prometheus::x::Transport>(
                        std::x::in_place_index<0>(),
                        ppto.bindAddress,
                        ppto.metricsPath,
                        ppto.numThreads
                    );
                }
            ), options);
        } catch(std::exception& e) {
            return std::x::unexpected<util::Error>(util::Error(
                "Failed to construct Prometheus pull transport.",
                std::vector<std::string>{ std::string(e.what()) }
            ));
        }
    }
}
