#pragma once

#include <vector>

#include "metrics/options.hpp"

namespace dometer::config::metrics {
    struct Metrics {
        std::vector<dometer::metrics::Options> handlers;
    };
}
