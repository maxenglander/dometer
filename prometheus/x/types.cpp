#include "prometheus/x/types.hpp"

namespace prometheus::x {
    bool FamilyNameAndTimeSeriesCount::operator==(const FamilyNameAndTimeSeriesCount& other) const {
        return other.family_name == family_name && other.time_series_count == time_series_count;
    }
}
