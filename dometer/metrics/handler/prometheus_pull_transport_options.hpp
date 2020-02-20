#pragma once

#include <string>

namespace dometer::metrics::handler {
    struct PrometheusPullTransportOptions {
        const std::string bindAddress;
        const std::string metricsPath;
        const unsigned int numThreads;
    };
}
