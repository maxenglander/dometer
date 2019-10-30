#pragma once

#include <stdint.h>
#include <tuple>

#include "metrics/metric.hpp"

namespace Dometer::Metrics {
    template<typename V, typename... L>
    struct Observation {
        Observation(const Metric<V, L...>& metric, V value, std::tuple<L...> labelValues)
            : metric(metric), value(value), labelValues(labelValues) {};
        const Metric<V, L...>& metric;
        const V value;
        const std::tuple<L...> labelValues;
    };

    template<typename V, typename... L>
    class ObservationBuilder {
        virtual Observation<V, L...> build() const = 0;
    };
}
