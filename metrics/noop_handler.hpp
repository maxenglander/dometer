#pragma once

#include "metrics/handler.hpp"
#include "metrics/observation.hpp"

namespace Dometer::Metrics {
    class NoopHandler : public Handler {
        public:
            template<typename... T>
            void handle(Observation<T...>) {};
    };
}
