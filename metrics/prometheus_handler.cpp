#include <type_traits>

#include "metrics/prometheus_handler.hpp"
#include "metrics/prometheus_types.hpp"
#include "prometheus/registry.h"
#include "util/lru_map.hpp"

namespace Util = Dometer::Util;

namespace Dometer::Metrics {
    PrometheusHandler::PrometheusHandler(std::shared_ptr<prometheus::Registry> registry)
        :   PrometheusHandler(registry, 3)
    {}

    PrometheusHandler::PrometheusHandler(std::shared_ptr<prometheus::Registry> registry, size_t maxTimeSeries)
        :   registry(registry), metricCache(maxTimeSeries)
    {
        metricCache.onEvict([this](auto k, auto v) {
            this->handleMetricEviction(k, v);
        });
    }

    void PrometheusHandler::handleMetricEviction(prometheus::ext::AnyMetricPtr anyMetricPtr,
                                                 prometheus::ext::FamilyNameAndTimeSeriesCount meta) {
        visit([this, &meta](auto&& metricPtr) {
            auto search = metricFamilies.find(meta.familyName);

            if(search == metricFamilies.end()) return;

            auto anyFamilyRef = search->second;

            using MetricType = std::decay_t<decltype(*metricPtr)>;

            if(auto familyPtr = get_if<prometheus::ext::FamilyRef<MetricType>>(&anyFamilyRef)) {
                prometheus::Family<MetricType>& family = *familyPtr;
                family.Remove(metricPtr);
            }
        }, anyMetricPtr);
    }
}
