#include <iostream>
#include <memory>
#include <type_traits>
#include <vector>

#include "dometer/metrics/handler/prometheus/handler.hpp"
#include "prometheus/registry.h"
#include "prometheus/x/types.hpp"
#include "dometer/util/lru_map.hpp"

namespace util = dometer::util;

namespace dometer::metrics::handler::prometheus {
    Handler::CacheEvictor::CacheEvictor(
            std::unordered_map<std::string, ::prometheus::x::AnyFamilyRef>& metricFamilies,
            ::prometheus::x::FamilyNameAndTimeSeriesCount& meta)
        :   metricFamilies(metricFamilies),
            meta(meta)
    {
    }
                       
    Handler::Handler(size_t maxTimeSeries,
                std::shared_ptr<::prometheus::Registry> registry,
                std::vector<std::shared_ptr<::prometheus::x::Transport>> transports)
        :   metricCache(maxTimeSeries), registry(registry), transports(transports)
    {
        metricCache.onEvict([this](::prometheus::x::AnyMetricPtr anyMetricPtr,
                                   ::prometheus::x::FamilyNameAndTimeSeriesCount meta) {
            CacheEvictor evictFromCache(metricFamilies, meta);
            visit(evictFromCache, anyMetricPtr);
        });
    }

    Handler::Handler(const Handler& handler)
        : metricCache(handler.metricCache),
          metricFamilies(handler.metricFamilies),
          registry(handler.registry),
          transports(handler.transports)
    {
    }
}
