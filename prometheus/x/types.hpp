#pragma once

#include <memory>

#include "prometheus/exposer.h"
#include "prometheus/family.h"
#include "prometheus/gateway.h"
#include "prometheus/histogram.h"
#include "std/x/variant.hpp"

namespace prometheus::x {
    struct FamilyNameAndTimeSeriesCount {
        bool operator==(const FamilyNameAndTimeSeriesCount& other) const;
        std::string family_name;
        size_t time_series_count;
    };

    template<typename T>
    using FamilyRef = std::reference_wrapper<prometheus::Family<T>>;
    using AnyFamilyRef = std::x::variant<FamilyRef<prometheus::Histogram>>;
    using AnyMetricPtr = std::x::variant<prometheus::Histogram*>;
    using Transport = std::x::variant<prometheus::Exposer, prometheus::Gateway>;
}
