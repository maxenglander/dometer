#include "experimental/variant.hpp"
#include "metrics/prometheus_lru_map.hpp"
#include "metrics/prometheus_types.hpp"
#include "prometheus/counter.h"

namespace util = dometer::util;
using namespace std::experimental;

namespace dometer::metrics {
    PrometheusLRUMap::PrometheusLRUMap(size_t maxTimeSeries)
        :    util::LRUMap<prometheus::ext::AnyMetricPtr, prometheus::ext::FamilyNameAndTimeSeriesCount>(0),
             maxTimeSeries(maxTimeSeries), numTimeSeries(0)
    {
        util::LRUMap<prometheus::ext::AnyMetricPtr,
                     prometheus::ext::FamilyNameAndTimeSeriesCount>::onEvict([this](auto metricPtr, auto meta) {
            this->numTimeSeries -= meta.timeSeriesCount;
        });

        util::LRUMap<prometheus::ext::AnyMetricPtr,
                     prometheus::ext::FamilyNameAndTimeSeriesCount>::onInsert([this](auto metricPtr, auto meta) {
            this->numTimeSeries += meta.timeSeriesCount;
        });
    }

    bool PrometheusLRUMap::shouldEvict() {
        return numTimeSeries > maxTimeSeries;
    }
}
