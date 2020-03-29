#pragma once

#include <memory>

#include "prometheus/counter.h"
#include "prometheus/exposer.h"
#include "prometheus/family.h"
#include "prometheus/gateway.h"
#include "prometheus/summary.h"
#include "std/x/variant.hpp"

namespace prometheus::x {
    struct FamilyNameAndTimeSeriesCount {
        bool operator==(const FamilyNameAndTimeSeriesCount& other) const;
        std::string family_name;
        uint8_t time_series_count;
    };

    template<typename T>
    using FamilyRef = std::reference_wrapper<prometheus::Family<T>>;
    using AnyFamilyRef = std::x::variant<FamilyRef<prometheus::Counter>, FamilyRef<prometheus::Summary>>;
    using AnyMetricPtr = std::x::variant<prometheus::Counter*, prometheus::Summary*>;
    using Transport = std::x::variant<prometheus::Exposer, prometheus::Gateway>;
}
