#include <string>

#include "dometer/metrics/handler/prometheus/metric_cache.hpp"
#include "prometheus/counter.h"
#include "prometheus/x/types.hpp"
#include "std/x/variant.hpp"

namespace util = dometer::util;

namespace dometer::metrics::handler::prometheus {
    metric_cache::time_series_changer::time_series_changer(metric_cache& parent, bool increment)
        : parent(parent), increment(increment) {
    }

    template <class MetricPtr, class Meta>
    void metric_cache::time_series_changer::operator()(MetricPtr metric_ptr, Meta meta) {
        if(increment) {
            parent.num_time_series += meta.time_series_count;
        } else {
            parent.num_time_series -= meta.time_series_count;
        }
    }

    metric_cache::metric_cache(size_t max_time_series)
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

    metric_cache::metric_cache(const metric_cache& src)
        : util::lru_map<::prometheus::x::AnyMetricPtr,
                        ::prometheus::x::FamilyNameAndTimeSeriesCount>(src),
          decrement_time_series(src.decrement_time_series),
          increment_time_series(src.increment_time_series),
          max_time_series(src.max_time_series),
          num_time_series(src.num_time_series)
    {}

    metric_cache::metric_cache(metric_cache&& src)
        : util::lru_map<::prometheus::x::AnyMetricPtr,
                        ::prometheus::x::FamilyNameAndTimeSeriesCount>(src),
          decrement_time_series(src.decrement_time_series),
          increment_time_series(src.increment_time_series),
          max_time_series(src.max_time_series),
          num_time_series(src.num_time_series)
    {}

    bool metric_cache::should_evict() {
        return num_time_series > max_time_series;
    }
}
