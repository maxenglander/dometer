#include "metrics/counter.hpp"
#include "metrics/observation.hpp"
#include "metrics/summary.hpp"
#include "metrics/handler/handler.hpp"
#include "x/variant.hpp"

namespace dometer::metrics::handler {
    template<typename... L>
    void Handler::increment(const dometer::metrics::Counter<L...>& counter,
                            dometer::metrics::Observation<uint64_t, L...> observation) {
        std::x::visit(std::x::overloaded(
            [counter, observation](auto handler) {
                handler.increment(counter, observation);
            }
        ), this->handler);
    }

    template<typename... L>
    void Handler::observe(const dometer::metrics::Summary<L...>& summary,
                          dometer::metrics::Observation<double, L...> observation) {
        std::x::visit(std::x::overloaded(
            [summary, observation](auto handler) {
                handler.observe(summary, observation);
            }
        ), this->handler);
    }
}
