#pragma once

#include <vector>

#include "dometer/metrics/handler/prometheus_transport_options.hpp"

namespace dometer::metrics::handler {
    struct PrometheusOptions {
        const unsigned int maxTimeSeries;
        const std::vector<PrometheusTransportOptions> transports;
    };
}
