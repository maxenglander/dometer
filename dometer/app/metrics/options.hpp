#pragma once

#include <vector>

#include "dometer/metrics/handler/options.hpp"

namespace dometer::app::metrics {
    struct options {
        std::vector<dometer::metrics::handler::options> handlers;
    };
}