#pragma once

#include <vector>

#include "dometer/metrics/handler/options.hpp"

namespace dometer::metrics {
    struct Options {
        const std::vector<dometer::metrics::handler::Options> handlers;
    };
}
