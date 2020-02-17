#include <type_traits>
#include <vector>

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
        :   PrometheusHandler(10000, registry)
    {}

    PrometheusHandler::PrometheusHandler(size_t maxTimeSeries)
        :   PrometheusHandler(maxTimeSeries, std::make_shared<prometheus::Registry>())
    {}

    PrometheusHandler::PrometheusHandler(size_t maxTimeSeries, std::shared_ptr<prometheus::Registry> registry)
        :   PrometheusHandler(maxTimeSeries, registry, std::vector<prometheus::x::Transport>())
    {}

    PrometheusHandler::PrometheusHandler(size_t maxTimeSeries,
                std::shared_ptr<prometheus::Registry> registry,
                std::vector<prometheus::x::Transport> transports)
        :   metricCache(maxTimeSeries), registry(registry), transports(transports)
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
