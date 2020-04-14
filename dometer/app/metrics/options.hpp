#pragma once

#include <map>
#include <vector>

#include "dometer/metrics/handler/options.hpp"

namespace dometer::app::metrics {
    struct options {
        std::map<std::string, std::string> additional_labels;
        std::vector<dometer::metrics::handler::options> handlers;
    };
}
