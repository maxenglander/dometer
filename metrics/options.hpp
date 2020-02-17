#pragma once

#include <vector>

#include "metrics/handler/options.hpp"

namespace dometer::metrics {
    struct Options {
        const std::vector<dometer::metrics::handler::Options> handlers;
    };
}
