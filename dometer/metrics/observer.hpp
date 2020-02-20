#pragma once

#include <vector>

#include "dometer/metrics/counter.hpp"
#include "dometer/metrics/handler/handler.hpp"
#include "dometer/metrics/observation.hpp"
#include "dometer/metrics/summary.hpp"

namespace dometer::metrics {
    class Observer {
        public:
            Observer() = delete;
            Observer(std::vector<dometer::metrics::handler::Handler>);
            template<typename... L> void increment(const Counter<L...>&, Observation<uint64_t, L...>);
            template<typename... L> void observe(const Summary<L...>&, Observation<double, L...>);
        private:
            std::vector<dometer::metrics::handler::Handler> handlers;
    };
}

#include "dometer/metrics/observer.ipp"
