#pragma once

#include <string>

namespace dometer::metrics::handler::prometheus {
    struct PullTransportOptions {
        const std::string bindAddress;
        const std::string metricsPath;
        const unsigned int numThreads;
    };
}
