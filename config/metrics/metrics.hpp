#pragma once

#include <vector>

#include "metrics/handler/options.hpp"

namespace dometer::config::metrics {
    struct Metrics {
        std::vector<dometer::metrics::handler::Options> handlers;
    };
}
