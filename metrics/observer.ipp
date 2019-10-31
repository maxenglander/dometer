#pragma once

#include <iostream>

#include "metrics/counter.hpp"
#include "metrics/observation.hpp"
#include "metrics/observer.hpp"
#include "metrics/summary.hpp"

namespace Dometer::Metrics {
    template<typename Handler>
    Observer<Handler>::Observer(std::shared_ptr<Handler> handler) : handler(handler) {}

    template<typename Handler>
    template<typename... L>
    void Observer<Handler>::increment(const Counter<L...>& counter, Observation<uint64_t, L...> observation) {
        handler->increment(counter, observation);
    }

    template<typename Handler>
    template<typename... L>
    void Observer<Handler>::observe(const Summary<L...>& summary, Observation<double, L...> observation) {
        handler->observe(summary, observation);
    }
}
