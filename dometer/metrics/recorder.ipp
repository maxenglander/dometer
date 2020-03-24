#pragma once

#include <iostream>

#include "dometer/metrics/counter.hpp"
#include "dometer/metrics/observation.hpp"
#include "dometer/metrics/recorder.hpp"
#include "dometer/metrics/summary.hpp"

namespace dometer::metrics {
    template<typename... L>
    void recorder::increment(const counter<L...>& counter, observation<uint64_t, L...> observation) {
        for(auto it = handlers.begin(); it < handlers.end(); it++) {
            it->increment(counter, observation);
        }
    }

    template<typename... L>
    void recorder::record(const summary<L...>& summary, observation<double, L...> observation) {
        for(auto it = handlers.begin(); it < handlers.end(); it++) {
            it->record(summary, observation);
        }
    }
}
