#pragma once

#include <vector>

#include "dometer/metrics/counter.hpp"
#include "dometer/metrics/handler/handler.hpp"
#include "dometer/metrics/observation.hpp"
#include "dometer/metrics/summary.hpp"

namespace dometer::metrics {
    class recorder {
        public:
            recorder() = delete;
            recorder(std::vector<dometer::metrics::handler::handler>);
            template<typename... L> void increment(const counter<L...>&, observation<uint64_t, L...>);
            template<typename... L> void record(const summary<L...>&, observation<double, L...>);
        private:
            std::vector<dometer::metrics::handler::handler> handlers;
    };
}

#include "dometer/metrics/recorder.ipp"
