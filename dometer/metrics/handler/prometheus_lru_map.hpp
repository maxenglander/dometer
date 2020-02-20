#pragma once

#include "dometer/metrics/handler/prometheus_types.hpp"
#include "prometheus/counter.h"
#include "prometheus/summary.h"
#include "dometer/util/lru_map.hpp"

namespace util = dometer::util;

namespace dometer::metrics::handler {
    class PrometheusLRUMap
            : public util::LRUMap<prometheus::x::AnyMetricPtr, prometheus::x::FamilyNameAndTimeSeriesCount> {
        public:
            PrometheusLRUMap(size_t maxTimeSeries);
        protected:
            bool shouldEvict() override;
        private:
            const size_t maxTimeSeries;
            size_t numTimeSeries;
    };
}
