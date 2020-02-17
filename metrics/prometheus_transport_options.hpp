#pragma once

#include "metrics/prometheus_pull_transport_options.hpp"
#include "x/variant.hpp"

namespace dometer::metrics {
    using PrometheusTransportOptions = std::x::variant<PrometheusPullTransportOptions>;
}
