#pragma once

#include "metrics/handler/prometheus_options.hpp"
#include "x/variant.hpp"

namespace dometer::metrics::handler {
    using Options = std::x::variant<PrometheusOptions>;
}
