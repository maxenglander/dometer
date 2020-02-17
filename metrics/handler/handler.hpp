#pragma once

#include "metrics/counter.hpp"
#include "metrics/observation.hpp"
#include "metrics/summary.hpp"
#include "metrics/handler/prometheus_handler.hpp"
#include "x/variant.hpp"

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

#include "metrics/handler/handler.ipp"
