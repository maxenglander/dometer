#pragma once

#include <string>

#include "dometer/metrics/prometheus_options.hpp"
#include "std/x/variant.hpp"

namespace dometer::config::metrics::handler {
    using Handler = std::x::variant<dometer::metrics::PrometheusOptions>;
}
