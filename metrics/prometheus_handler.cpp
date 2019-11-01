#include <type_traits>

#include "metrics/prometheus_handler.hpp"
#include "prometheus/registry.h"
#include "util/lru_map.hpp"

namespace Util = Dometer::Util;

namespace Dometer::Metrics {
    PrometheusHandler::PrometheusHandler(std::shared_ptr<prometheus::Registry> registry)
        :   PrometheusHandler(registry, 10)
    {}

    PrometheusHandler::PrometheusHandler(std::shared_ptr<prometheus::Registry> registry, size_t maxSize)
        :   registry(registry), metricCache(maxSize)
    {
        metricCache.onEvict([this](auto k, auto v) {
            this->handleMetricEviction(k, v);
        });
    }

    void PrometheusHandler::handleMetricEviction(prometheus::AnyMetricPtr anyMetricPtr, std::string name) {
        visit([this, name](auto&& metricPtr) {
            auto search = metricFamilies.find(name);

            if(search == metricFamilies.end()) return;

            auto anyFamilyRef = search->second;

            using MetricType = std::decay_t<decltype(*metricPtr)>;

            if(auto familyPtr = get_if<prometheus::FamilyRef<MetricType>>(&anyFamilyRef)) {
                prometheus::Family<MetricType>& family = *familyPtr;
                family.Remove(metricPtr);
            }
        }, anyMetricPtr);
    }
}
