#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#include "dometer/metrics/counter.hpp"
#include "dometer/metrics/handler/prometheus/handler.hpp"
#include "dometer/metrics/metric.hpp"
#include "dometer/util/error.hpp"
#include "prometheus/counter.h"
#include "prometheus/registry.h"
#include "prometheus/x/types.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::metrics::handler::prometheus {
    handler::cache_evictor::cache_evictor(
            std::unordered_map<std::string, ::prometheus::x::AnyFamilyRef>& metric_families,
            ::prometheus::x::FamilyNameAndTimeSeriesCount& meta)
        :   _metric_families(metric_families),
            _meta(meta)
    {}

    template <class MetricPtr>
    void handler::cache_evictor::operator()(MetricPtr&& metric_ptr) {
        auto search = _metric_families.find(_meta.family_name);
        if(search == _metric_families.end()) return;
        auto any_family_ref = search->second;

        using MetricType = typename std::decay<decltype(*metric_ptr)>::type;
        if(auto family_ptr = std::x::get_if<::prometheus::x::FamilyRef<MetricType>>(&any_family_ref)) {
            ::prometheus::Family<MetricType>& family = *family_ptr;
            family.Remove(metric_ptr);
        }
    }
                      
    handler::handler(size_t max_time_series,
                std::shared_ptr<::prometheus::Registry> registry,
                std::vector<std::shared_ptr<::prometheus::x::Transport>> transports)
        :   _metric_cache(max_time_series), _registry(registry), _transports(transports)
    {
        _metric_cache.on_evict([this](::prometheus::x::AnyMetricPtr any_metric_ptr,
                                      ::prometheus::x::FamilyNameAndTimeSeriesCount meta) {
            cache_evictor evict_from_cache(_metric_families, meta);
            visit(evict_from_cache, any_metric_ptr);
        });
    }

    handler::handler(const handler& handler)
        : _metric_cache(handler._metric_cache),
          _metric_families(handler._metric_families),
          _registry(handler._registry),
          _transports(handler._transports)
    {}

    template<typename T>
    void handler::cache_metric(T* metric, ::prometheus::x::FamilyNameAndTimeSeriesCount meta) {
        _metric_cache.put(metric, meta);
    }

    template<typename T, typename BuilderFn>
    std::x::expected<::prometheus::x::FamilyRef<T>, util::error> handler::get_or_build_metric_family(
            std::string name, std::string description, BuilderFn new_builder) {
        auto search = _metric_families.find(name);
        if(search == _metric_families.end()) {
            const ::prometheus::x::FamilyRef<T> family_ref
                = std::ref(new_builder().Name(name).Help(description).Register(*_registry));
            _metric_families.insert({name, ::prometheus::x::AnyFamilyRef(family_ref)});
            search = _metric_families.find(name);
        }

        const ::prometheus::x::AnyFamilyRef any_family_ref = search->second;
        if(auto family_ref_ptr = std::x::get_if<::prometheus::x::FamilyRef<T>>(&any_family_ref)) {
            ::prometheus::x::FamilyRef<T> family_ref = *family_ref_ptr;
            return family_ref;
        }

        return std::x::unexpected<util::error>(util::error(
            "A metric with this name, but a different type, already exists"
        ));
    }

    void handler::increment(const dometer::metrics::counter& counter,
                            std::map<std::string, std::string> labels,
                            uint64_t value) {
        auto metric_family_ref = get_or_build_metric_family<::prometheus::Counter, decltype(::prometheus::BuildCounter)>(
            counter.name, counter.description, ::prometheus::BuildCounter
        );
        
        if(metric_family_ref) {
            ::prometheus::Family<::prometheus::Counter>& metric_family = *metric_family_ref;
            ::prometheus::Counter& prom_counter = metric_family.Add(labels);
            prom_counter.Increment(value);
            cache_metric(&prom_counter, { counter.name, 1 });
        }
    }

    void handler::record(const dometer::metrics::histogram& histogram,
                         std::map<std::string, std::string> labels,
                         double value) {
        auto metric_family_ref = get_or_build_metric_family<::prometheus::Histogram, decltype(::prometheus::BuildHistogram)>(
            histogram.name, histogram.description, ::prometheus::BuildHistogram
        );
        
        if(metric_family_ref) {
            ::prometheus::Family<::prometheus::Histogram>& metric_family = *metric_family_ref;
            ::prometheus::Histogram& prom_histogram = metric_family.Add(labels, histogram.buckets);
            prom_histogram.Observe(value);
            cache_metric(&prom_histogram, { histogram.name, 2/*count and sum*/ + histogram.buckets.size() + 1/*+Inf*/ });
        }
    }
}
