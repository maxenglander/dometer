#pragma once

#include <functional>
#include <map>
#include <string>
#include <tuple>
#include <utility>

#include "x/expected.hpp"
#include "x/variant.hpp"

#include "metrics/label_helper.hpp"
#include "metrics/counter.hpp"
#include "metrics/metric.hpp"
#include "metrics/observation.hpp"
#include "metrics/prometheus_handler.hpp"
#include "metrics/prometheus_lru_map.hpp"
#include "metrics/prometheus_types.hpp"

#include "prometheus/counter.h"
#include "prometheus/summary.h"

#include "util/error.hpp"

namespace util = dometer::util;
using namespace std::x;

namespace dometer::metrics {
    template<typename T>
    void PrometheusHandler::cacheMetric(T* metric, prometheus::ext::FamilyNameAndTimeSeriesCount meta) {
        metricCache.put(metric, meta);
    }

    template<typename T, typename BuilderFn>
    expected<prometheus::ext::FamilyRef<T>, util::Error> PrometheusHandler::getOrBuildMetricFamily(
            std::string name, std::string description, BuilderFn newBuilder) {
        auto search = metricFamilies.find(name);

        if(search == metricFamilies.end()) {
            const prometheus::ext::FamilyRef<T> familyRef
                = std::ref(newBuilder().Name(name).Help(description).Register(*registry));
            metricFamilies.insert({name, prometheus::ext::AnyFamilyRef(familyRef)});
            search = metricFamilies.find(name);
        }

        const prometheus::ext::AnyFamilyRef anyFamilyRef = search->second;

        if(auto familyRefPtr = get_if<prometheus::ext::FamilyRef<T>>(&anyFamilyRef)) {
            prometheus::ext::FamilyRef<T> familyRef = *familyRefPtr;
            return familyRef;
        }

        return unexpected<util::Error>(util::Error{
            "A metric with this name, but a different type, already exists", 0
        });
    }

    template<typename... L>
    void PrometheusHandler::increment(const Counter<L...>& counter, Observation<uint64_t, L...> observation) {
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
    void PrometheusHandler::observe(const Summary<L...>& summary, Observation<double, L...> observation) {
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
