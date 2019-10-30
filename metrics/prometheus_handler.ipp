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
    void PrometheusHandler::handle(Observation<double, L...> observation) {
        switch(observation.metric.type) {
            case Type::SUMMARY:
                handleSummary(observation);
            default:
                break;
        }
    }

    template<typename... L>
    void PrometheusHandler::handle(Observation<uint64_t, L...> observation) {
        switch(observation.metric.type) {
            case Type::COUNTER:
                handleCounter(observation);
            default:
                break;
        }
    }

    template<typename... L>
    void PrometheusHandler::handleCounter(Observation<uint64_t, L...> observation) {
        const Metric<uint64_t, L...>& metric = observation.metric;

        auto search = counters.find(metric.name);
        if(search == counters.end()) {
            counters.insert({metric.name, std::ref(prometheus::BuildCounter()
                .Name(metric.name)
                .Help(metric.description)
                .Register(*registry))});
            search = counters.find(metric.name);
        }

        std::map<std::string, std::string> labels
            = LabelHelper::createLabelMap(metric.labels, observation.labelValues);
        prometheus::Family<prometheus::Counter>& counter = search->second;
        counter.Add(labels).Increment(observation.value);
    }

    template<typename... L>
    void PrometheusHandler::handleSummary(Observation<double, L...> observation) {
        const Metric<double, L...>& metric = observation.metric;

        auto search = summaries.find(metric.name);
        if(search == summaries.end()) {
            summaries.insert({metric.name, std::ref(prometheus::BuildSummary()
                .Name(metric.name)
                .Help(metric.description)
                .Register(*registry))});
            search = summaries.find(metric.name);
        }

        std::map<std::string, std::string> labels
            = LabelHelper::createLabelMap(metric.labels, observation.labelValues);
        prometheus::Family<prometheus::Summary>& summary = search->second;
        summary.Add(labels, prometheus::Summary::Quantiles{
            {0.5, 0.5}, {0.9, 0.1}, {0.95, 0.005}, {0.99, 0.001}
        }).Observe(observation.value);
    }
}
