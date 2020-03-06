#pragma once

#include <iostream>

#include "dometer/metrics/counter.hpp"
#include "dometer/metrics/observation.hpp"
#include "dometer/metrics/observer.hpp"
#include "dometer/metrics/summary.hpp"

namespace dometer::metrics {
    template<typename... L>
    void observer::increment(const Counter<L...>& counter, Observation<uint64_t, L...> observation) {
        for(auto it = handlers.begin(); it < handlers.end(); it++) {
            it->increment(counter, observation);
        }
    }

    template<typename... L>
    void observer::observe(const Summary<L...>& summary, Observation<double, L...> observation) {
        for(auto it = handlers.begin(); it < handlers.end(); it++) {
            it->observe(summary, observation);
        }
    }
}
