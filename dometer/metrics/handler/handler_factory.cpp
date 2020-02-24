#include "dometer/metrics/handler/handler.hpp"
#include "dometer/metrics/handler/handler_factory.hpp"
#include "dometer/metrics/handler/options.hpp"
#include "dometer/metrics/handler/prometheus_handler_factory.hpp"
#include "dometer/metrics/handler/prometheus_options.hpp"
#include "std/x/expected.hpp"
#include "std/x/variant.hpp"

namespace util = dometer::util;

namespace dometer::metrics::handler {
    std::x::expected<Handler, util::Error> HandlerFactory::makeHandler(Options options) {
        auto concreteHandler = std::x::visit(std::x::overloaded(
            [](PrometheusOptions po) {
                return PrometheusHandlerFactory::makeHandler(po);
            }
        ), options);

        if(concreteHandler) {
            return Handler(*concreteHandler);
        } else {
            return std::x::unexpected<util::Error>(util::Error(
                "Failed to create prometheus metrics handler.",
                concreteHandler.error()
            ));
        }
    }
}
