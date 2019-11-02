#include "experimental/variant.hpp"
#include "metrics/prometheus_lru_map.hpp"
#include "metrics/prometheus_types.hpp"
#include "prometheus/counter.h"

namespace Util = Dometer::Util;
using namespace std::experimental;

namespace Dometer::Metrics {
    PrometheusLRUMap::PrometheusLRUMap(size_t maxTimeSeries)
        :    Util::LRUMap<prometheus::ext::AnyMetricPtr, prometheus::ext::FamilyNameAndTimeSeriesCount>(0),
             maxTimeSeries(maxTimeSeries), numTimeSeries(0)
    {
        Util::LRUMap<prometheus::ext::AnyMetricPtr,
                     prometheus::ext::FamilyNameAndTimeSeriesCount>::onEvict([this](auto metricPtr, auto meta) {
            this->numTimeSeries -= meta.timeSeriesCount;
        });

        Util::LRUMap<prometheus::ext::AnyMetricPtr,
                     prometheus::ext::FamilyNameAndTimeSeriesCount>::onInsert([this](auto metricPtr, auto meta) {
            this->numTimeSeries += meta.timeSeriesCount;
        });
    }

    bool PrometheusLRUMap::shouldEvict() {
        return numTimeSeries > maxTimeSeries;
    }
}
