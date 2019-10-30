#pragma once

#include <stdint.h>
#include <tuple>

#include "metrics/metric.hpp"

namespace Dometer::Metrics {
    template<typename... T>
    struct Observation {
        Observation(const Metric<T...>& metric, std::tuple<T...> labelValues, uint64_t value)
            : metric(metric), labelValues(labelValues), value(value) {};
        const Metric<T...>& metric;
        const std::tuple<T...> labelValues;
        const uint64_t value;
    };

    template<typename... T>
    class ObservationBuilder {
        virtual Observation<T...> build() const = 0;
    };
}
