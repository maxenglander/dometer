#include <memory>
#include <utility>
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
    std::x::expected<std::unique_ptr<handler>, util::error> handler_factory::make_handler(options options) {
        auto result = std::x::visit(std::x::overloaded(
            [](dometer::metrics::handler::prometheus::options po) {
                return dometer::metrics::handler::prometheus::handler_factory::make_handler(po);
            }
        ), options);

        if(!result) {
            return std::x::unexpected<util::error>(util::error(
                "Failed to create metrics handler.",
                result.error()
            ));
        }

        return std::move(*result);
    }

    std::x::expected<std::vector<std::unique_ptr<handler>>, util::error> handler_factory::make_handlers(std::vector<options> optionss) {
        std::vector<std::unique_ptr<dometer::metrics::handler::handler>> handlers;

        for(auto it = optionss.begin(); it < optionss.end(); it++) {
            auto result = make_handler(*it);
            if(!result) {
                return std::x::unexpected<util::error>(util::error(
                    "Failed to create metrics handler.",
                    result.error()
                ));
            }
            handlers.push_back(std::move(*result));
        }

        return handlers;
    }
}
