#pragma once

#include <vector>

#include "dometer/metrics/handler/options.hpp"

namespace dometer::config::metrics {
    struct Metrics {
        std::vector<dometer::metrics::handler::Options> handlers;
    };
}
