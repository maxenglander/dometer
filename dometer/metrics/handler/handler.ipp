#include "dometer/metrics/counter.hpp"
#include "dometer/metrics/observation.hpp"
#include "dometer/metrics/summary.hpp"
#include "dometer/metrics/handler/handler.hpp"
#include "std/x/variant.hpp"

namespace dometer::metrics::handler {
    template<typename... L>
    Handler::CounterIncrementer<L...>::CounterIncrementer(
            const dometer::metrics::Counter<L...>& counter,
            dometer::metrics::Observation<uint64_t, L...>& observation)
        :   counter(counter),
            observation(observation) {
    }

    
    template<typename... L>
    template<class ConcreteHandler>
    void Handler::CounterIncrementer<L...>::operator()(ConcreteHandler& handler) {
        handler.increment(counter, observation);
    }

    template<typename... L>
    Handler::SummaryObserver<L...>::SummaryObserver(
            const dometer::metrics::Summary<L...>& summary,
            dometer::metrics::Observation<double, L...>& observation)
        :   summary(summary),
            observation(observation) {
    }

    template<typename... L>
    template<class ConcreteHandler>
    void Handler::SummaryObserver<L...>::operator()(ConcreteHandler& handler) {
        handler.observe(summary, observation);
    }

    template<typename... L>
    void Handler::increment(const dometer::metrics::Counter<L...>& counter,
                            dometer::metrics::Observation<uint64_t, L...> observation) {
        CounterIncrementer<L...> incrementCount(counter, observation); 
        std::x::visit(incrementCount, this->concreteHandler);
    }

    template<typename... L>
    void Handler::observe(const dometer::metrics::Summary<L...>& summary,
                          dometer::metrics::Observation<double, L...> observation) {
        SummaryObserver<L...> observeSummary(summary, observation);
        std::x::visit(observeSummary, this->concreteHandler);
    }
}
