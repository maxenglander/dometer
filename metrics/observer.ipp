#pragma once

#include <iostream>

#include "metrics/counter.hpp"
#include "metrics/observation.hpp"
#include "metrics/observer.hpp"
#include "metrics/summary.hpp"

namespace dometer::metrics {
    template<typename... L>
    void Observer::increment(const Counter<L...>& counter, Observation<uint64_t, L...> observation) {
        std::cout << "checking handler size" << std::endl;
        std::cout << "handlers contains" << handlers.size() << std::endl;
        for(auto it = handlers.begin(); it < handlers.end(); it++) {
            it->increment(counter, observation);
        }
    }

    template<typename... L>
    void Observer::observe(const Summary<L...>& summary, Observation<double, L...> observation) {
        std::cout << "checking handler size" << std::endl;
        std::cout << "handlers contains" << handlers.size() << std::endl;
        for(auto it = handlers.begin(); it < handlers.end(); it++) {
            it->observe(summary, observation);
        }
    }
}
