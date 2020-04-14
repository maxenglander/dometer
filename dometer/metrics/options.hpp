#pragma once

#include <map>
#include <vector>

#include "dometer/metrics/handler/options.hpp"

namespace dometer::metrics {
    struct options {
        const std::map<std::string, std::string> additional_labels;
        const std::vector<dometer::metrics::handler::options> handlers;
    };
}
