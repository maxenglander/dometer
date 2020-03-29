#include <memory>
#include <vector>

#include "dometer/metrics/handler/prometheus/pull_transport_options.hpp"
#include "dometer/metrics/handler/prometheus/transport_factory.hpp"
#include "dometer/metrics/handler/prometheus/transport_options.hpp"
#include "dometer/util/error.hpp"
#include "prometheus/x/types.hpp"
#include "std/x/expected.hpp"
#include "std/x/variant.hpp"

namespace util = dometer::util;

namespace dometer::metrics::handler::prometheus {
    std::x::expected<std::shared_ptr<::prometheus::x::Transport>, util::error> transport_factory::make_transport(
            transport_options options) {
        try {
            return std::x::visit(std::x::overloaded(
                [](pull_transport_options ppto) {
                    return std::make_shared<::prometheus::x::Transport>(
                        std::x::in_place_index<0>(),
                        ppto.bind_address,
                        ppto.metrics_path,
                        ppto.num_threads
                    );
                }
            ), options);
        } catch(std::exception& e) {
            return std::x::unexpected<util::error>(util::error(
                "Failed to construct pull transport.",
                std::vector<std::string>{ std::string(e.what()) }
            ));
        }
    }
}
