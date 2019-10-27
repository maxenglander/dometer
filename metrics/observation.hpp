#pragma once

#include <stdint.h>
#include <tuple>

#include "metrics/descriptor.hpp"

namespace Dometer::Metrics {
    template<typename... T>
    struct Observation {
        Observation(const Descriptor<T...>& descriptor, std::tuple<T...> labelValues, uint64_t value)
            : descriptor(descriptor), labelValues(labelValues), value(value) {};
        const Descriptor<T...>& descriptor;
        const std::tuple<T...> labelValues;
        const uint64_t value;
    };

    template<typename... T>
    class ObservationBuilder {
        virtual Observation<T...> build() const = 0;
    };
}
