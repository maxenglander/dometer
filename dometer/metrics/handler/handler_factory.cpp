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
    std::x::expected<handler, util::error> handler_factory::make_handler(options options) {
        auto concrete_handler = std::x::visit(std::x::overloaded(
            [](dometer::metrics::handler::prometheus::options po) {
                return dometer::metrics::handler::prometheus::handler_factory::make_handler(po);
            }
        ), options);

        if(concrete_handler) {
            return handler(*concrete_handler);
        } else {
            return std::x::unexpected<util::error>(util::error(
                "Failed to create prometheus metrics handler.",
                concrete_handler.error()
            ));
        }
    }

    std::x::expected<std::vector<handler>, util::error> handler_factory::make_handlers(std::vector<options> optionss) {
        std::vector<dometer::metrics::handler::handler> handlers;

        for(auto it = optionss.begin(); it < optionss.end(); it++) {
            auto handler = make_handler(*it);
            if(!handler) {
                return std::x::unexpected<util::error>(util::error(
                    "Failed to create metrics handler.",
                    handler.error()
                ));
            }
            handlers.push_back(*handler);
        }

        return handlers;
    }
}
