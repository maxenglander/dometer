#pragma once

#include <vector>

#include "config/metrics/handler/handler.hpp"

namespace dometer::config::metrics {
    struct Metrics {
        std::vector<dometer::config::metrics::handler::Handler> handlers;
    };
}
