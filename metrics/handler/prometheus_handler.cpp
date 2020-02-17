#include <type_traits>

#include "metrics/handler/prometheus_handler.hpp"
#include "metrics/handler/prometheus_types.hpp"
#include "prometheus/registry.h"
#include "util/lru_map.hpp"

namespace util = dometer::util;

namespace dometer::metrics::handler {
    PrometheusHandler::PrometheusHandler()
        :   PrometheusHandler(std::make_shared<prometheus::Registry>())
    {}

    PrometheusHandler::PrometheusHandler(std::shared_ptr<prometheus::Registry> registry)
        :   PrometheusHandler(registry, 10000)
    {}

    PrometheusHandler::PrometheusHandler(size_t maxTimeSeries)
        :   PrometheusHandler(std::make_shared<prometheus::Registry>(), maxTimeSeries)
    {}

    PrometheusHandler::PrometheusHandler(std::shared_ptr<prometheus::Registry> registry, size_t maxTimeSeries)
        :   registry(registry), metricCache(maxTimeSeries)
    {
        metricCache.onEvict([this](auto k, auto v) {
            this->handleMetricEviction(k, v);
        });
    }

    void PrometheusHandler::handleMetricEviction(prometheus::x::AnyMetricPtr anyMetricPtr,
                                                 prometheus::x::FamilyNameAndTimeSeriesCount meta) {
        visit([this, &meta](auto&& metricPtr) {
            auto search = metricFamilies.find(meta.familyName);

            if(search == metricFamilies.end()) return;

            auto anyFamilyRef = search->second;

            using MetricType = std::decay_t<decltype(*metricPtr)>;

            if(auto familyPtr = get_if<prometheus::x::FamilyRef<MetricType>>(&anyFamilyRef)) {
                prometheus::Family<MetricType>& family = *familyPtr;
                family.Remove(metricPtr);
            }
        }, anyMetricPtr);
    }
}
