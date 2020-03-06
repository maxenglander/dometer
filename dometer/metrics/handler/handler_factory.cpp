#include <vector>

#include "dometer/metrics/handler/handler.hpp"
#include "dometer/metrics/handler/handler_factory.hpp"
#include "dometer/metrics/handler/options.hpp"
#include "dometer/metrics/handler/prometheus/handler_factory.hpp"
#include "dometer/metrics/handler/prometheus/options.hpp"
#include "std/x/expected.hpp"
#include "std/x/variant.hpp"

namespace util = dometer::util;

namespace dometer::metrics::handler {
    std::x::expected<Handler, util::Error> HandlerFactory::makeHandler(Options options) {
        auto concreteHandler = std::x::visit(std::x::overloaded(
            [](dometer::metrics::handler::prometheus::Options po) {
                return dometer::metrics::handler::prometheus::HandlerFactory::makeHandler(po);
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

    std::x::expected<std::vector<Handler>, util::Error> HandlerFactory::makeHandlers(std::vector<Options> optionss) {
        std::vector<dometer::metrics::handler::Handler> handlers;

        for(auto it = optionss.begin(); it < optionss.end(); it++) {
            auto handler = makeHandler(*it);
            if(!handler) {
                return std::x::unexpected<util::Error>(util::Error(
                    "Failed to create metrics handler.",
                    handler.error()
                ));
            }
            handlers.push_back(*handler);
        }

        return handlers;
    }
}
