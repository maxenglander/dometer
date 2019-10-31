#pragma once

#include <tuple>

#include "metrics/observation.hpp"

namespace Dometer::Metrics {
    template<typename V, typename... L>
    Observation<V, L...>::Observation(V value, std::tuple<L...> labelValues)
            :   value(value), labelValues(labelValues)
    {};
}
