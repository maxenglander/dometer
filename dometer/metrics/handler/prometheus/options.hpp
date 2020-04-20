#pragma once

#include <vector>

#include "dometer/metrics/handler/prometheus/transport_options.hpp"

namespace dometer::metrics::handler::prometheus {
    struct options {
        const unsigned int max_time_series;
        const std::vector<transport_options> transports;
    };
}
