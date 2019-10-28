#pragma once

#include <iostream>

#include "metrics/observation.hpp"
#include "metrics/observer.hpp"

namespace Dometer::Metrics {
    template<typename Handler>
    Observer<Handler>::Observer(std::shared_ptr<Handler> handler) : handler(handler) {}

    template<typename Handler>
    template<typename... T>
    void Observer<Handler>::observe(Observation<T...> observation) {
        std::cout << "observer: sending observation to handler" << std::endl;
        handler->handle(observation);
    }
}
