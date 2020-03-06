#pragma once

#include "dometer/metrics/handler/prometheus/options.hpp"
#include "std/x/variant.hpp"

namespace dometer::metrics::handler {
    using Options = std::x::variant<dometer::metrics::handler::prometheus::Options>;
}
