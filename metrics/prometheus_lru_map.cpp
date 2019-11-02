#include "metrics/prometheus_lru_map.hpp"

namespace Util = Dometer::Util;

namespace Dometer::Metrics {
    PrometheusLRUMap::PrometheusLRUMap(size_t maxTimeSeries)
        :    Util::LRUMap<prometheus::ext::AnyMetricPtr, std::string>(0),
             numTimeSeries(0), maxTimeSeries(maxTimeSeries)
    {}

    void PrometheusLRUMap::erase(prometheus::ext::AnyMetricPtr metricPtr) {
        Util::LRUMap<prometheus::ext::AnyMetricPtr, std::string>::erase(metricPtr);
    }

    void PrometheusLRUMap::insert(prometheus::ext::AnyMetricPtr metricPtr, std::string familyName) {
        Util::LRUMap<prometheus::ext::AnyMetricPtr, std::string>::insert(metricPtr, familyName);
    }

    bool PrometheusLRUMap::shouldEvict() {
        return numTimeSeries < maxTimeSeries;
    }
}
