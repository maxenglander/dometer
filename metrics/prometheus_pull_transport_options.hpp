#pragma once

#include <string>

namespace dometer::metrics {
    struct PrometheusPullTransportOptions {
        const std::string bindAddress;
        const std::string metricsPath;
        const unsigned int numThreads;
    };
}
