#include "dometer/metrics/handler/prometheus/lru_map.hpp"
#include "prometheus/counter.h"
#include "prometheus/x/types.hpp"
#include "std/x/variant.hpp"

namespace util = dometer::util;

namespace dometer::metrics::handler::prometheus {
    LRUMap::TimeSeriesChanger::TimeSeriesChanger(LRUMap& parent, bool increment)
        : parent(parent), increment(increment) {
    }

    template <class MetricPtr, class Meta>
    void LRUMap::TimeSeriesChanger::operator()(MetricPtr metriPtr, Meta meta) {
        if(increment) {
            parent.numTimeSeries -= meta.timeSeriesCount;
        } else {
            parent.numTimeSeries += meta.timeSeriesCount;
        }
    }

    LRUMap::LRUMap(size_t maxTimeSeries)
        :    util::LRUMap<::prometheus::x::AnyMetricPtr, ::prometheus::x::FamilyNameAndTimeSeriesCount>(0),
             decrementTimeSeries(TimeSeriesChanger(*this, false)),
             incrementTimeSeries(TimeSeriesChanger(*this, true)),
             maxTimeSeries(maxTimeSeries),
             numTimeSeries(0)
    {
        util::LRUMap<::prometheus::x::AnyMetricPtr,
                     ::prometheus::x::FamilyNameAndTimeSeriesCount>::onEvict(decrementTimeSeries);

        util::LRUMap<::prometheus::x::AnyMetricPtr,
                     ::prometheus::x::FamilyNameAndTimeSeriesCount>::onInsert(incrementTimeSeries);
    }

    bool LRUMap::shouldEvict() {
        return numTimeSeries > maxTimeSeries;
    }
}
