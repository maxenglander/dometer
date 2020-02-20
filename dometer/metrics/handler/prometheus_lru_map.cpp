#include "std/x/variant.hpp"
#include "dometer/metrics/handler/prometheus_lru_map.hpp"
#include "dometer/metrics/handler/prometheus_types.hpp"
#include "prometheus/counter.h"

namespace util = dometer::util;
using namespace std::x;

namespace dometer::metrics::handler {
    PrometheusLRUMap::PrometheusLRUMap(size_t maxTimeSeries)
        :    util::LRUMap<prometheus::x::AnyMetricPtr, prometheus::x::FamilyNameAndTimeSeriesCount>(0),
             maxTimeSeries(maxTimeSeries),
             numTimeSeries(0)
    {
        util::LRUMap<prometheus::x::AnyMetricPtr,
                     prometheus::x::FamilyNameAndTimeSeriesCount>::onEvict([this](auto metricPtr, auto meta) {
            this->numTimeSeries -= meta.timeSeriesCount;
        });

        util::LRUMap<prometheus::x::AnyMetricPtr,
                     prometheus::x::FamilyNameAndTimeSeriesCount>::onInsert([this](auto metricPtr, auto meta) {
            this->numTimeSeries += meta.timeSeriesCount;
        });
    }

    bool PrometheusLRUMap::shouldEvict() {
        return numTimeSeries > maxTimeSeries;
    }
}
