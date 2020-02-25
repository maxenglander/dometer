#pragma once

#include <vector>

#include "dometer/metrics/handler/options.hpp"

namespace dometer::app::metrics {
    struct Options {
        std::vector<dometer::metrics::handler::Options> handlers;
    };
}
