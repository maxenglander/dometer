#pragma once

#include <functional>
#include <map>
#include <string>
#include <tuple>

#include "metrics/label_helper.hpp"
#include "metrics/metric.hpp"
#include "metrics/observation.hpp"
#include "metrics/prometheus_handler.hpp"

#include "prometheus/counter.h"

namespace Dometer::Metrics {
    template<typename... T>
    void PrometheusHandler::handle(Observation<T...> observation) {
        switch(observation.metric.type) {
            case Type::COUNTER:
                handleCounter(observation);
            default:
                break;
        }
    }

    template<typename... T>
    void PrometheusHandler::handleCounter(Observation<T...> observation) {
        const Metric<T...>& metric = observation.metric;

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
}
