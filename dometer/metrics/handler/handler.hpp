#pragma once

#include "dometer/metrics/counter.hpp"
#include "dometer/metrics/observation.hpp"
#include "dometer/metrics/summary.hpp"
#include "dometer/metrics/handler/prometheus/handler.hpp"
#include "std/x/variant.hpp"

namespace dometer::metrics::handler {
    class handler {
        template<typename... L>
        class counter_incrementer {
            public:
                counter_incrementer(const dometer::metrics::counter<L...>&, dometer::metrics::observation<uint64_t, L...>&);
                template <class ConcreteHandler>
                void operator()(ConcreteHandler&);
            private:
                const dometer::metrics::counter<L...>& counter;
                dometer::metrics::observation<uint64_t, L...>& observation;
        };

        template<typename... L>
        class summary_observer {
            public:
                summary_observer(const dometer::metrics::summary<L...>&, dometer::metrics::observation<double, L...>&);
                template <class ConcreteHandler>
                void operator()(ConcreteHandler&);
            private:
                const dometer::metrics::summary<L...>& summary;
                dometer::metrics::observation<double, L...>& observation;
        };

        public:
            handler(dometer::metrics::handler::prometheus::handler);

            template<typename... L>
            void increment(const dometer::metrics::counter<L...>&, dometer::metrics::observation<uint64_t, L...>);

            template<typename... L>
            void observe(const dometer::metrics::summary<L...>&, dometer::metrics::observation<double, L...>);
        private:
             std::x::variant<dometer::metrics::handler::prometheus::handler> concrete_handler;
    };
}

#include "dometer/metrics/handler/handler.ipp"
