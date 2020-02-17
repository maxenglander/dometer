#pragma once

#include "metrics/prometheus_options.hpp"

namespace dometer::metrics {
    using Options = std::x::variant<PrometheusOptions>;
}
