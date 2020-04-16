#pragma once

#include "dometer/util/lru_map.hpp"
#include "prometheus/counter.h"
#include "prometheus/x/types.hpp"

namespace util = dometer::util;

namespace dometer::metrics::handler::prometheus {
    class metric_cache 
            : public util::lru_map<::prometheus::x::AnyMetricPtr, ::prometheus::x::FamilyNameAndTimeSeriesCount> {
        class time_series_changer {
            public:
                time_series_changer(metric_cache&, bool);
                template <class MetricPtr, class Meta>
                void operator()(MetricPtr, Meta);
            private:
                metric_cache& parent;
                bool increment;
        };

        public:
            metric_cache(size_t);
            metric_cache(metric_cache&&);
            metric_cache(const metric_cache&);
        protected:
            bool should_evict() override;
        private:
            time_series_changer decrement_time_series;
            time_series_changer increment_time_series;

            const size_t max_time_series;
            size_t num_time_series;
    };
}
