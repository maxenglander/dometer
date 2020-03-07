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
    handler::summary_observer<L...>::summary_observer(
            const dometer::metrics::summary<L...>& summary,
            dometer::metrics::observation<double, L...>& observation)
        :   summary(summary),
            observation(observation) {
    }

    template<typename... L>
    template<class ConcreteHandler>
    void handler::summary_observer<L...>::operator()(ConcreteHandler& handler) {
        handler.observe(summary, observation);
    }

    template<typename... L>
    void handler::increment(const dometer::metrics::counter<L...>& counter,
                            dometer::metrics::observation<uint64_t, L...> observation) {
        counter_incrementer<L...> incrementCount(counter, observation); 
        std::x::visit(incrementCount, this->concrete_handler);
    }

    template<typename... L>
    void handler::observe(const dometer::metrics::summary<L...>& summary,
                          dometer::metrics::observation<double, L...> observation) {
        summary_observer<L...> observeSummary(summary, observation);
        std::x::visit(observeSummary, this->concrete_handler);
    }
}
