#pragma once

#include <vector>

#include "metrics/counter.hpp"
#include "metrics/handler/handler.hpp"
#include "metrics/observation.hpp"
#include "metrics/summary.hpp"

namespace dometer::metrics {
    class Observer {
        public:
            Observer(std::vector<dometer::metrics::handler::Handler>);
            template<typename... L> void increment(const Counter<L...>&, Observation<uint64_t, L...>);
            template<typename... L> void observe(const Summary<L...>&, Observation<double, L...>);
        private:
            std::vector<dometer::metrics::handler::Handler> handlers;
    };
}

#include "metrics/observer.ipp"
