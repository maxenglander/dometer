#pragma once

#include <vector>

#include "dometer/metrics/counter.hpp"
#include "dometer/metrics/handler/handler.hpp"
#include "dometer/metrics/observation.hpp"
#include "dometer/metrics/summary.hpp"

namespace dometer::metrics {
    class observer {
        public:
            observer() = delete;
            observer(std::vector<dometer::metrics::handler::handler>);
            template<typename... L> void increment(const counter<L...>&, observation<uint64_t, L...>);
            template<typename... L> void observe(const summary<L...>&, observation<double, L...>);
        private:
            std::vector<dometer::metrics::handler::handler> handlers;
    };
}

#include "dometer/metrics/observer.ipp"
