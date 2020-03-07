#pragma once

#include "dometer/util/lru_map.hpp"
#include "prometheus/counter.h"
#include "prometheus/summary.h"
#include "prometheus/x/types.hpp"

namespace util = dometer::util;

namespace dometer::metrics::handler::prometheus {
    class lru_map
            : public util::lru_map<::prometheus::x::AnyMetricPtr, ::prometheus::x::FamilyNameAndTimeSeriesCount> {
        class time_series_changer {
            public:
                time_series_changer(lru_map&, bool);
                template <class MetricPtr, class Meta>
                void operator()(MetricPtr, Meta);
            private:
                lru_map& parent;
                bool increment;
        };

        public:
            lru_map(size_t max_timer_series);
        protected:
            bool should_evict() override;
        private:
            time_series_changer decrement_time_series;
            time_series_changer increment_time_series;

            const size_t max_time_series;
            size_t num_time_series;
    };
}
