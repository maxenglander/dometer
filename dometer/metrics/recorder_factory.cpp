#include <memory>
#include <utility>
#include <vector>

#include "dometer/metrics/handler/handler.hpp"
#include "dometer/metrics/handler/handler_factory.hpp"
#include "dometer/metrics/recorder.hpp"
#include "dometer/metrics/recorder_factory.hpp"
#include "dometer/metrics/options.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace dometer::metrics {
    std::x::expected<std::shared_ptr<recorder>, util::error> recorder_factory::make_recorder(options _options) {
        std::vector<std::unique_ptr<dometer::metrics::handler::handler>> handlers;

        for(auto it = _options.handlers.begin(); it < _options.handlers.end(); it++) {
            auto handler = dometer::metrics::handler::handler_factory::make_handler(*it);
            if(!handler)
                return std::x::unexpected<util::error>(util::error(
                    "Failed to create metrics handler.",
                    handler.error()
                ));
            handlers.push_back(std::move(*handler));
        }

        return std::make_shared<recorder>(_options.additional_labels, std::move(handlers));
    }
}
