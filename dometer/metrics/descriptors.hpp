#pragma once

#include "dometer/metrics/descriptor.hpp"

namespace dometer::metrics {
    class descriptors {
        public:
            descriptors() = delete;
            static const descriptor<std::string, std::string, std::string, bool> query;
    };
}
