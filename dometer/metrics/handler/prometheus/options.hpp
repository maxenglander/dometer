#pragma once

#include <vector>

#include "dometer/metrics/handler/prometheus/transport_options.hpp"

namespace dometer::metrics::handler::prometheus {
    struct Options {
        const unsigned int maxTimeSeries;
        const std::vector<TransportOptions> transports;
    };
}
