#pragma once

#include <functional>
#include <map>
#include <string>
#include <tuple>
#include <utility>

#include "experimental/expected.hpp"
#include "experimental/variant.hpp"

#include "metrics/label_helper.hpp"
#include "metrics/counter.hpp"
#include "metrics/metric.hpp"
#include "metrics/observation.hpp"
#include "metrics/prometheus_handler.hpp"

#include "prometheus/counter.h"
#include "prometheus/summary.h"

#include "util/error.hpp"
#include "util/lru_map.hpp"

namespace Util = Dometer::Util;
using namespace std::experimental;

namespace Dometer::Metrics {
    template<typename T>
    void PrometheusHandler::cacheMetric(T* metric, std::string name) {
        metricCache.put(metric, name);
    }

    template<typename T, typename BuilderFn>
    expected<prometheus::FamilyRef<T>, Util::Error> PrometheusHandler::getOrBuildMetricFamily(
            std::string name, std::string description, BuilderFn newBuilder) {
        auto search = metricFamilies.find(name);

        if(search == metricFamilies.end()) {
            const prometheus::FamilyRef<T> familyRef
                = std::ref(newBuilder().Name(name).Help(description).Register(*registry));
            metricFamilies.insert({name, prometheus::AnyFamilyRef(familyRef)});
            search = metricFamilies.find(name);
        }

        const prometheus::AnyFamilyRef anyFamilyRef = search->second;

        if(auto familyRefPtr = get_if<prometheus::FamilyRef<T>>(&anyFamilyRef)) {
            prometheus::FamilyRef<T> familyRef = *familyRefPtr;
            return familyRef;
        }

        return unexpected<Util::Error>(Util::Error{
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
            cacheMetric(&promCounter, counter.name);
            promCounter.Increment(observation.value);
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
            cacheMetric(&promSummary, summary.name);
            promSummary.Observe(observation.value);
        }
    }
}
