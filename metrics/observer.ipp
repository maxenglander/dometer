#pragma once

#include "metrics/observation.hpp"
#include "metrics/observer.hpp"

namespace Dometer::Metrics {
    template<typename... T>
    void Observer::observe(Observation<T...> observation) {
        handler.handle(observation);
    }
}
