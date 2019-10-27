#pragma once

#include "metrics/descriptor.hpp"

namespace Dometer::Metrics {
    class Descriptors {
        public:
            Descriptors() = delete;
            static const Descriptor<std::string, bool> QUERY;
    };
}
