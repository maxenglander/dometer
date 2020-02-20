#include "dometer/metrics/handler/handler.hpp"
#include "dometer/metrics/handler/handler_factory.hpp"
#include "dometer/metrics/handler/options.hpp"
#include "dometer/metrics/handler/prometheus_handler_factory.hpp"
#include "dometer/metrics/handler/prometheus_options.hpp"
#include "std/x/variant.hpp"

namespace dometer::metrics::handler {
    Handler HandlerFactory::makeHandler(Options options) {
        return Handler(std::x::visit(std::x::overloaded(
            [](PrometheusOptions po) {
                return PrometheusHandlerFactory::makeHandler(po);
            }
        ), options));
    }
}
