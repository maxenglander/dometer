#pragma once

#include "dometer/metrics/handler/prometheus_options.hpp"
#include "std/x/variant.hpp"

namespace dometer::metrics::handler {
    using Options = std::x::variant<PrometheusOptions>;
}
