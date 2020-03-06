#include <iostream>
#include <memory>
#include <vector>

#include "dometer/metrics/handler/factory.hpp"
#include "dometer/metrics/handler/handler.hpp"
#include "dometer/metrics/observer.hpp"
#include "dometer/metrics/observer_factory.hpp"
#include "dometer/metrics/options.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace dometer::metrics {
    std::x::expected<std::shared_ptr<observer>, util::error> ObserverFactory::makeObserver(Options options) {
        std::vector<dometer::metrics::handler::Handler> handlers;

        for(auto it = options.handlers.begin(); it < options.handlers.end(); it++) {
            auto handler = dometer::metrics::handler::Factory::makeHandler(*it);
            if(!handler)
                return std::x::unexpected<util::error>(util::error(
                    "Failed to create metrics handler.",
                    handler.error()
                ));
            handlers.push_back(*handler);
        }

        return std::make_shared<observer>(handlers);
    }
}
