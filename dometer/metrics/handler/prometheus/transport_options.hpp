#pragma once

#include "dometer/metrics/handler/prometheus/pull_transport_options.hpp"
#include "std/x/variant.hpp"

namespace dometer::metrics::handler::prometheus {
    using TransportOptions = std::x::variant<PullTransportOptions>;
}
