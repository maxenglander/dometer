#pragma once

#include "dometer/metrics/handler/prometheus_pull_transport_options.hpp"
#include "std/x/variant.hpp"

namespace dometer::metrics::handler {
    using PrometheusTransportOptions = std::x::variant<PrometheusPullTransportOptions>;
}
