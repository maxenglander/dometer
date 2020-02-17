#pragma once

#include "metrics/observation.hpp"

namespace dometer::metrics::handler {
    class Handler {
        public:
            template<typename... L> void handle(dometer::metrics::Observation<double, L...>) {};
            template<typename... L> void handle(dometer::metrics::Observation<uint64_t, L...>) {};
    };
}
