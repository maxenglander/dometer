#pragma once

#include <string>

#include "metrics/prometheus_options.hpp"
#include "x/variant.hpp"

namespace dometer::config::metrics::handler {
    using Handler = std::x::variant<dometer::metrics::PrometheusOptions>;
}
