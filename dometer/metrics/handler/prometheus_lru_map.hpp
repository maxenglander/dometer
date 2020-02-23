#pragma once

#include "dometer/util/lru_map.hpp"
#include "prometheus/counter.h"
#include "prometheus/summary.h"
#include "prometheus/x/types.hpp"

namespace util = dometer::util;

namespace dometer::metrics::handler {
    class PrometheusLRUMap
            : public util::LRUMap<prometheus::x::AnyMetricPtr, prometheus::x::FamilyNameAndTimeSeriesCount> {
        class TimeSeriesChanger {
            public:
                TimeSeriesChanger(PrometheusLRUMap&, bool);
                template <class MetricPtr, class Meta>
                void operator()(MetricPtr, Meta);
            private:
                PrometheusLRUMap& parent;
                bool increment;
        };

        public:
            PrometheusLRUMap(size_t maxTimeSeries);
        protected:
            bool shouldEvict() override;
        private:
            TimeSeriesChanger decrementTimeSeries;
            TimeSeriesChanger incrementTimeSeries;

            const size_t maxTimeSeries;
            size_t numTimeSeries;
    };
}
