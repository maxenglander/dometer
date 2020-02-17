#pragma once

#include <vector>

#include "metrics/prometheus_transport_options.hpp"

namespace dometer::metrics {
    struct PrometheusOptions {
        const unsigned int maxTimeSeries;
        const std::vector<PrometheusTransportOptions> transports;
    };
}
