#pragma once

#include <vector>

#include "dometer/metrics/prometheus_transport_options.hpp"

namespace dometer::config::metrics::handler {
    struct Prometheus {
        const unsigned int maxTimeSeries;
        std::vector<dometer::metrics::PrometheusTransportOptions> transports;
    };
}
