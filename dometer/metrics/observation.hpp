#pragma once

#include <tuple>

#include "dometer/metrics/metric.hpp"

namespace dometer::metrics {
    template<typename V, typename... L>
    struct observation {
        observation(V value, std::tuple<L...> label_values);
        const V value;
        const std::tuple<L...> label_values;
    };

    template<typename V, typename... L>
    class observation_builder {
        virtual observation<V, L...> build() const = 0;
    };
}

#include "dometer/metrics/observation.ipp"
