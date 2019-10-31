#pragma once

#include <memory>

#include "metrics/counter.hpp"
#include "metrics/observation.hpp"
#include "metrics/summary.hpp"

namespace Dometer::Metrics {
    template<typename Handler>
    class Observer {
        public:
            Observer(std::shared_ptr<Handler>);
            template<typename... L> void increment(const Counter<L...>&, Observation<uint64_t, L...>);
            template<typename... L> void observe(const Summary<L...>&, Observation<double, L...>);
        private:
            std::shared_ptr<Handler> handler;
    };
}

#include "metrics/observer.ipp"
