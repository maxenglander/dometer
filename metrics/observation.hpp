#pragma once

#include <tuple>

#include "metrics/metric.hpp"

namespace dometer::metrics {
    template<typename V, typename... L>
    struct Observation {
        Observation(V value, std::tuple<L...> labelValues);
        const V value;
        const std::tuple<L...> labelValues;
    };

    template<typename V, typename... L>
    class ObservationBuilder {
        virtual Observation<V, L...> build() const = 0;
    };
}

#include "metrics/observation.ipp"
