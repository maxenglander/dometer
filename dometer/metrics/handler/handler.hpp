#pragma once

#include "dometer/metrics/counter.hpp"
#include "dometer/metrics/observation.hpp"
#include "dometer/metrics/summary.hpp"
#include "dometer/metrics/handler/prometheus_handler.hpp"
#include "std/x/variant.hpp"

namespace dometer::metrics::handler {
    class Handler {
        public:
            Handler(PrometheusHandler);

            template<typename... L>
            void increment(const dometer::metrics::Counter<L...>&, dometer::metrics::Observation<uint64_t, L...>);

            template<typename... L>
            void observe(const dometer::metrics::Summary<L...>&, dometer::metrics::Observation<double, L...>);
        private:
             std::x::variant<PrometheusHandler> handler;
    };
}

#include "dometer/metrics/handler/handler.ipp"
