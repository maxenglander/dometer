#include "metrics/handler/handler.hpp"
#include "metrics/handler/handler_factory.hpp"
#include "metrics/handler/options.hpp"
#include "metrics/handler/prometheus_handler_factory.hpp"
#include "metrics/handler/prometheus_options.hpp"
#include "x/variant.hpp"

namespace dometer::metrics::handler {
    Handler HandlerFactory::makeHandler(Options options) {
        return Handler(std::x::visit(std::x::overloaded(
            [](PrometheusOptions po) {
                return PrometheusHandlerFactory::makeHandler(po);
            }
        ), options));
    }
}
