#pragma once

#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <utility>

#include "dometer/metrics/label_helper.hpp"
#include "dometer/metrics/counter.hpp"
#include "dometer/metrics/handler/prometheus_handler.hpp"
#include "dometer/metrics/handler/prometheus_lru_map.hpp"
#include "dometer/metrics/metric.hpp"
#include "dometer/metrics/observation.hpp"
#include "prometheus/counter.h"
#include "prometheus/summary.h"
#include "prometheus/x/types.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::metrics::handler {
    template <class MetricPtr>
    void PrometheusHandler::CacheEvictor::operator()(MetricPtr&& metricPtr) {
        auto search = metricFamilies.find(meta.familyName);
        if(search == metricFamilies.end()) return;
        auto anyFamilyRef = search->second;

        using MetricType = typename std::decay<decltype(*metricPtr)>::type;
        if(auto familyPtr = get_if<prometheus::x::FamilyRef<MetricType>>(&anyFamilyRef)) {
            prometheus::Family<MetricType>& family = *familyPtr;
            family.Remove(metricPtr);
        }
    }

    template<typename T>
    void PrometheusHandler::cacheMetric(T* metric, prometheus::x::FamilyNameAndTimeSeriesCount meta) {
        metricCache.put(metric, meta);
    }

    template<typename T, typename BuilderFn>
    std::x::expected<prometheus::x::FamilyRef<T>, util::Error> PrometheusHandler::getOrBuildMetricFamily(
            std::string name, std::string description, BuilderFn newBuilder) {
        auto search = metricFamilies.find(name);
        if(search == metricFamilies.end()) {
            const prometheus::x::FamilyRef<T> familyRef
                = std::ref(newBuilder().Name(name).Help(description).Register(*registry));
            metricFamilies.insert({name, prometheus::x::AnyFamilyRef(familyRef)});
            search = metricFamilies.find(name);
        }

        const prometheus::x::AnyFamilyRef anyFamilyRef = search->second;
        if(auto familyRefPtr = get_if<prometheus::x::FamilyRef<T>>(&anyFamilyRef)) {
            prometheus::x::FamilyRef<T> familyRef = *familyRefPtr;
            return familyRef;
        }

        return std::x::unexpected<util::Error>(util::Error(
            "A metric with this name, but a different type, already exists"
        ));
    }

    template<typename... L>
    void PrometheusHandler::increment(const dometer::metrics::Counter<L...>& counter,
            dometer::metrics::Observation<uint64_t, L...> observation) {
        auto metricFamilyRef = getOrBuildMetricFamily<prometheus::Counter, decltype(prometheus::BuildCounter)>(
            counter.name, counter.description, prometheus::BuildCounter
        );
        
        if(metricFamilyRef) {
            prometheus::Family<prometheus::Counter>& metricFamily = *metricFamilyRef;
            prometheus::Counter& promCounter = metricFamily.Add(
                LabelHelper::createLabelMap(counter.labels, observation.labelValues)
            );
            promCounter.Increment(observation.value);
            cacheMetric(&promCounter, { counter.name, 1 });
        }
    }

    template<typename... L>
    void PrometheusHandler::observe(const dometer::metrics::Summary<L...>& summary,
            dometer::metrics::Observation<double, L...> observation) {
        auto metricFamilyRef = getOrBuildMetricFamily<prometheus::Summary, decltype(prometheus::BuildSummary)>(
            summary.name, summary.description, prometheus::BuildSummary
        );
        
        if(metricFamilyRef) {
            prometheus::Family<prometheus::Summary>& metricFamily = *metricFamilyRef;
            prometheus::Summary& promSummary = metricFamily.Add(
                LabelHelper::createLabelMap(summary.labels, observation.labelValues),
                prometheus::Summary::Quantiles{
                    {0.5, 0.5}, {0.9, 0.1}, {0.95, 0.005}, {0.99, 0.001}
                }
            );
            promSummary.Observe(observation.value);
            cacheMetric(&promSummary, { summary.name, 2 + 4});
        }
    }
}
