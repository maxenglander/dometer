#pragma once

#include "experimental/variant.hpp"
#include "prometheus/counter.h"
#include "prometheus/family.h"
#include "prometheus/summary.h"

using namespace std::experimental;

namespace prometheus::ext {
    template<typename T>
    using FamilyRef = std::reference_wrapper<prometheus::Family<T>>;
    using AnyFamilyRef = variant<FamilyRef<prometheus::Counter>, FamilyRef<prometheus::Summary>>;
    using AnyMetricPtr = variant<prometheus::Counter*, prometheus::Summary*>;
}


