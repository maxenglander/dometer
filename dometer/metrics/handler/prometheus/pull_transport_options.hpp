#pragma once

#include <string>

namespace dometer::metrics::handler::prometheus {
    struct pull_transport_options {
        const std::string bind_address;
        const std::string metrics_path;
        const unsigned int num_threads;
    };
}
