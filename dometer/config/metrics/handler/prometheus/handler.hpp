#pragma once

#include <vector>

#include "dometer/metrics/prometheus_transport_options.hpp"

namespace dometer::config::metrics::handler::prometheus {
    struct Prometheus {
        const unsigned int maxTimeSeries;
        std::vector<dometer::metrics::handler::prometheus::TransportOptions> transports;
    };
}
