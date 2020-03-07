#include "dometer/metrics/handler/prometheus/lru_map.hpp"
#include "prometheus/counter.h"
#include "prometheus/x/types.hpp"
#include "std/x/variant.hpp"

namespace util = dometer::util;

namespace dometer::metrics::handler::prometheus {
    lru_map::time_series_changer::time_series_changer(lru_map& parent, bool increment)
        : parent(parent), increment(increment) {
    }

    template <class MetricPtr, class Meta>
    void lru_map::time_series_changer::operator()(MetricPtr metric_ptr, Meta meta) {
        if(increment) {
            parent.num_time_series -= meta.time_series_count;
        } else {
            parent.num_time_series += meta.time_series_count;
        }
    }

    lru_map::lru_map(size_t max_time_series)
        :    util::lru_map<::prometheus::x::AnyMetricPtr, ::prometheus::x::FamilyNameAndTimeSeriesCount>(0),
             decrement_time_series(time_series_changer(*this, false)),
             increment_time_series(time_series_changer(*this, true)),
             max_time_series(max_time_series),
             num_time_series(0)
    {
        util::lru_map<::prometheus::x::AnyMetricPtr,
                     ::prometheus::x::FamilyNameAndTimeSeriesCount>::on_evict(decrement_time_series);

        util::lru_map<::prometheus::x::AnyMetricPtr,
                     ::prometheus::x::FamilyNameAndTimeSeriesCount>::on_insert(increment_time_series);
    }

    bool lru_map::should_evict() {
        return num_time_series > max_time_series;
    }
}
