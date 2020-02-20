#pragma once

#include <tuple>

#include "dometer/metrics/observation.hpp"

namespace dometer::metrics {
    template<typename V, typename... L>
    Observation<V, L...>::Observation(V value, std::tuple<L...> labelValues)
            :   value(value), labelValues(labelValues)
    {};
}
