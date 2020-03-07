#pragma once

#include <tuple>

#include "dometer/metrics/observation.hpp"

namespace dometer::metrics {
    template<typename V, typename... L>
    observation<V, L...>::observation(V value, std::tuple<L...> label_values)
            :   value(value), label_values(label_values)
    {};
}
