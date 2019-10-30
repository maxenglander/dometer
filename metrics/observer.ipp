#pragma once

#include <iostream>

#include "metrics/observation.hpp"
#include "metrics/observer.hpp"

namespace Dometer::Metrics {
    template<typename Handler>
    Observer<Handler>::Observer(std::shared_ptr<Handler> handler) : handler(handler) {}

    template<typename Handler>
    template<typename... L>
    void Observer<Handler>::observe(Observation<uint64_t, L...> observation) {
        handler->handle(observation);
    }

    template<typename Handler>
    template<typename... L>
    void Observer<Handler>::observe(Observation<double, L...> observation) {
        handler->handle(observation);
    }
}
