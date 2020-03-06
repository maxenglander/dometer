#pragma once

#include "dometer/metrics/handler/prometheus/pull_transport_options.hpp"
#include "std/x/variant.hpp"

namespace dometer::metrics::handler::prometheus {
    using transport_options = std::x::variant<pull_transport_options>;
}
