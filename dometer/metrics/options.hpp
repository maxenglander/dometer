#pragma once

#include <vector>

#include "dometer/metrics/handler/options.hpp"

namespace dometer::metrics {
    struct options {
        const std::vector<dometer::metrics::handler::options> handlers;
    };
}
