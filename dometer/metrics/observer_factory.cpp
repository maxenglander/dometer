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
    std::x::expected<std::shared_ptr<observer>, util::error> observer_factory::make_observer(options _options) {
        std::vector<dometer::metrics::handler::handler> handlers;

        for(auto it = _options.handlers.begin(); it < _options.handlers.end(); it++) {
            auto handler = dometer::metrics::handler::factory::make_handler(*it);
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
