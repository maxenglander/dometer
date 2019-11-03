#pragma once

#include "metrics/prometheus_types.hpp"
#include "prometheus/counter.h"
#include "prometheus/summary.h"
#include "util/lru_map.hpp"

namespace util = dometer::util;

namespace dometer::metrics {
    class PrometheusLRUMap
            : public util::LRUMap<prometheus::ext::AnyMetricPtr, prometheus::ext::FamilyNameAndTimeSeriesCount> {
        public:
            PrometheusLRUMap(size_t maxTimeSeries);
        protected:
            bool shouldEvict() override;
        private:
            const size_t maxTimeSeries;
            size_t numTimeSeries;
    };
}
