#pragma once

#include "dometer/metrics/handler/prometheus/options.hpp"
#include "std/x/variant.hpp"

namespace dometer::metrics::handler {
    using options = std::x::variant<dometer::metrics::handler::prometheus::options>;
}
