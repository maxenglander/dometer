#pragma once

#include <vector>

#include "config/metrics/handler/prometheus/transport/transport.hpp"

namespace dometer::config::metrics::handler::prometheus {
    struct Prometheus {
        const unsigned int maxTimeSeries;
        std::vector<dometer::config::metrics::handler::prometheus::transport::Transport> transports;
    };
}
