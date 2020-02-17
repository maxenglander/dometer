#pragma once

#include <memory>

#include "prometheus/counter.h"
#include "prometheus/exposer.h"
#include "prometheus/family.h"
#include "prometheus/gateway.h"
#include "prometheus/summary.h"
#include "x/variant.hpp"

using namespace std::x;

namespace prometheus::x {
    struct FamilyNameAndTimeSeriesCount {
        std::string familyName;
        uint8_t timeSeriesCount;
    };

    template<typename T>
    using FamilyRef = std::reference_wrapper<prometheus::Family<T>>;
    using AnyFamilyRef = variant<FamilyRef<prometheus::Counter>, FamilyRef<prometheus::Summary>>;
    using AnyMetricPtr = variant<prometheus::Counter*, prometheus::Summary*>;

    using Transport = variant<prometheus::Exposer, prometheus::Gateway>;
}
