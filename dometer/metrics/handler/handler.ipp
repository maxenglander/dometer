#include "dometer/metrics/counter.hpp"
#include "dometer/metrics/observation.hpp"
#include "dometer/metrics/summary.hpp"
#include "dometer/metrics/handler/handler.hpp"
#include "std/x/variant.hpp"

namespace dometer::metrics::handler {
    template<typename... L>
    handler::counter_incrementer<L...>::counter_incrementer(
            const dometer::metrics::counter<L...>& counter,
            dometer::metrics::observation<uint64_t, L...>& observation)
        :   counter(counter),
            observation(observation) {
    }

    
    template<typename... L>
    template<class ConcreteHandler>
    void handler::counter_incrementer<L...>::operator()(ConcreteHandler& handler) {
        handler.increment(counter, observation);
    }

    template<typename... L>
    handler::summary_recorder<L...>::summary_recorder(
            const dometer::metrics::summary<L...>& summary,
            dometer::metrics::observation<double, L...>& observation)
        :   summary(summary),
            observation(observation) {
    }

    template<typename... L>
    template<class ConcreteHandler>
    void handler::summary_recorder<L...>::operator()(ConcreteHandler& handler) {
        handler.record(summary, observation);
    }

    template<typename... L>
    void handler::increment(const dometer::metrics::counter<L...>& counter,
                            dometer::metrics::observation<uint64_t, L...> observation) {
        counter_incrementer<L...> incrementCount(counter, observation); 
        std::x::visit(incrementCount, this->concrete_handler);
    }

    template<typename... L>
    void handler::record(const dometer::metrics::summary<L...>& summary,
                          dometer::metrics::observation<double, L...> observation) {
        summary_recorder<L...> record_summary(summary, observation);
        std::x::visit(record_summary, this->concrete_handler);
    }
}
