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
    handler::cache_evictor::cache_evictor(
            std::unordered_map<std::string, ::prometheus::x::AnyFamilyRef>& metric_families,
            ::prometheus::x::FamilyNameAndTimeSeriesCount& meta)
        :   metric_families(metric_families),
            meta(meta)
    {
    }
                       
    handler::handler(size_t max_time_series,
                std::shared_ptr<::prometheus::Registry> registry,
                std::vector<std::shared_ptr<::prometheus::x::Transport>> transports)
        :   metric_cache(max_time_series), registry(registry), transports(transports)
    {
        metric_cache.on_evict([this](::prometheus::x::AnyMetricPtr any_metric_ptr,
                                   ::prometheus::x::FamilyNameAndTimeSeriesCount meta) {
            cache_evictor evict_from_cache(metric_families, meta);
            visit(evict_from_cache, any_metric_ptr);
        });
    }

    handler::handler(const handler& handler)
        : metric_cache(handler.metric_cache),
          metric_families(handler.metric_families),
          registry(handler.registry),
          transports(handler.transports)
    {
    }
}
