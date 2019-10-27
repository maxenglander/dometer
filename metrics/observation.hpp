#pragma once

#include <stdint.h>
#include <tuple>

#include "metrics/descriptor.hpp"

namespace Dometer::Metrics {
    template<typename T...>
    struct Observation {
        const Descriptor<T...>& descriptor;
        const tuple<T...> labelValues;
        const uint64_t value;
    };
}
