#pragma once

#include <functional>
#include <map>
#include <string>
#include <tuple>

#include "metrics/label_helper.hpp"
#include "metrics/counter.hpp"
#include "metrics/metric.hpp"
#include "metrics/observation.hpp"
#include "metrics/prometheus_handler.hpp"

#include "prometheus/counter.h"
#include "prometheus/summary.h"

namespace Dometer::Metrics {
    template<typename... L>
    void PrometheusHandler::increment(const Counter<L...>& counter, Observation<uint64_t, L...> observation) {
        auto search = counters.find(counter.name);
        if(search == counters.end()) {
            counters.insert({counter.name, std::ref(prometheus::BuildCounter()
                .Name(counter.name)
                .Help(counter.description)
                .Register(*registry))});
            search = counters.find(counter.name);
        }

        std::map<std::string, std::string> labels
            = LabelHelper::createLabelMap(counter.labels, observation.labelValues);
        prometheus::Family<prometheus::Counter>& promCounter = search->second;
        promCounter.Add(labels).Increment(observation.value);
    }

    template<typename... L>
    void PrometheusHandler::observe(const Summary<L...>& summary, Observation<double, L...> observation) {
        auto search = summaries.find(summary.name);
        if(search == summaries.end()) {
            summaries.insert({summary.name, std::ref(prometheus::BuildSummary()
                .Name(summary.name)
                .Help(summary.description)
                .Register(*registry))});
            search = summaries.find(summary.name);
        }

        std::map<std::string, std::string> labels
            = LabelHelper::createLabelMap(summary.labels, observation.labelValues);
        prometheus::Family<prometheus::Summary>& promSummary = search->second;
        promSummary.Add(labels, prometheus::Summary::Quantiles{
            {0.5, 0.5}, {0.9, 0.1}, {0.95, 0.005}, {0.99, 0.001}
        }).Observe(observation.value);
    }
}
