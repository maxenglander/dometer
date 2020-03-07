#pragma once

#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <utility>

#include "dometer/metrics/label_helper.hpp"
#include "dometer/metrics/counter.hpp"
#include "dometer/metrics/handler/prometheus/handler.hpp"
#include "dometer/metrics/handler/prometheus/lru_map.hpp"
#include "dometer/metrics/metric.hpp"
#include "dometer/metrics/observation.hpp"
#include "prometheus/counter.h"
#include "prometheus/summary.h"
#include "prometheus/x/types.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::metrics::handler::prometheus {
    template <class MetricPtr>
    void handler::cache_evictor::operator()(MetricPtr&& metric_ptr) {
        auto search = metric_families.find(meta.family_name);
        if(search == metric_families.end()) return;
        auto any_family_ref = search->second;

        using MetricType = typename std::decay<decltype(*metric_ptr)>::type;
        if(auto family_ptr = get_if<::prometheus::x::FamilyRef<MetricType>>(&any_family_ref)) {
            ::prometheus::Family<MetricType>& family = *family_ptr;
            family.Remove(metric_ptr);
        }
    }

    template<typename T>
    void handler::cache_metric(T* metric, ::prometheus::x::FamilyNameAndTimeSeriesCount meta) {
        metric_cache.put(metric, meta);
    }

    template<typename T, typename BuilderFn>
    std::x::expected<::prometheus::x::FamilyRef<T>, util::error> handler::get_or_build_metric_family(
            std::string name, std::string description, BuilderFn new_builder) {
        auto search = metric_families.find(name);
        if(search == metric_families.end()) {
            const ::prometheus::x::FamilyRef<T> family_ref
                = std::ref(new_builder().Name(name).Help(description).Register(*registry));
            metric_families.insert({name, ::prometheus::x::AnyFamilyRef(family_ref)});
            search = metric_families.find(name);
        }

        const ::prometheus::x::AnyFamilyRef any_family_ref = search->second;
        if(auto family_ref_ptr = get_if<::prometheus::x::FamilyRef<T>>(&any_family_ref)) {
            ::prometheus::x::FamilyRef<T> family_ref = *family_ref_ptr;
            return family_ref;
        }

        return std::x::unexpected<util::error>(util::error(
            "A metric with this name, but a different type, already exists"
        ));
    }

    template<typename... L>
    void handler::increment(const dometer::metrics::counter<L...>& counter,
            dometer::metrics::observation<uint64_t, L...> observation) {
        auto metric_family_ref = get_or_build_metric_family<::prometheus::Counter, decltype(::prometheus::BuildCounter)>(
            counter.name, counter.description, ::prometheus::BuildCounter
        );
        
        if(metric_family_ref) {
            ::prometheus::Family<::prometheus::Counter>& metric_family = *metric_family_ref;
            ::prometheus::Counter& prom_counter = metric_family.Add(
                label_helper::create_label_map(counter.labels, observation.label_values)
            );
            prom_counter.Increment(observation.value);
            cache_metric(&prom_counter, { counter.name, 1 });
        }
    }

    template<typename... L>
    void handler::observe(const dometer::metrics::summary<L...>& summary,
            dometer::metrics::observation<double, L...> observation) {
        auto metric_family_ref = get_or_build_metric_family<::prometheus::Summary, decltype(::prometheus::BuildSummary)>(
            summary.name, summary.description, ::prometheus::BuildSummary
        );
        
        if(metric_family_ref) {
            ::prometheus::Family<::prometheus::Summary>& metric_family = *metric_family_ref;
            ::prometheus::Summary& prom_summary = metric_family.Add(
                label_helper::create_label_map(summary.labels, observation.label_values),
                ::prometheus::Summary::Quantiles{
                    {0.5, 0.5}, {0.9, 0.1}, {0.95, 0.005}, {0.99, 0.001}
                }
            );
            prom_summary.Observe(observation.value);
            cache_metric(&prom_summary, { summary.name, 2 + 4});
        }
    }
}
