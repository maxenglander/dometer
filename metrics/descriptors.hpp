#pragma once

#include "metrics/descriptor.hpp"

namespace Dometer::Metrics {
    class Descriptors {
        public:
            Descriptors() = delete;
            const static Descriptor<std::string, bool> QUERY;
    };
}
