#pragma once

#include <string>

namespace dometer::config::metrics::handler::prometheus::transport {
    struct Exposer {
        const std::string bindAddress;
        const unsigned int numThreads;
        const std::string metricsPath;
    };
}
