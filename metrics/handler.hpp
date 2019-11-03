#pragma once

#include "metrics/observation.hpp"

namespace dometer::metrics {
    class Handler {
        public:
            template<typename... L> void handle(Observation<double, L...>) {};
            template<typename... L> void handle(Observation<uint64_t, L...>) {};
    };
}
