#pragma once

#include "metrics/observation.hpp"

namespace Dometer::Metrics {
    class Handler {
        public:
            template<typename... T> void handle(Observation<T...>) {};
    };
}
