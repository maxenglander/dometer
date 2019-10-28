#pragma once

#include <map>
#include <string>
#include <tuple>

#include "metrics/descriptor.hpp"
#include "metrics/label_helper.hpp"
#include "metrics/observation.hpp"
#include "metrics/prometheus_handler.hpp"

#include "prometheus/counter.h"

namespace Dometer::Metrics {
    template<typename... T>
    void PrometheusHandler::handle(Observation<T...> observation) {
        switch(observation.descriptor.type) {
            case Type::COUNTER:
                handleCounter(observation);
        }
    }

    template<typename... T>
    void PrometheusHandler::handleCounter(Observation<T...> observation) {
        Descriptor<T...>& descriptor = observation.descriptor;

        auto search = counters.find(descriptor.name);
        if(!search) {
            counters[descriptor.name] = registry.Add<prometheus::Counter>(descriptor.name, descriptor.description, {});
        }

        std::map<std::string, std::string> labels
            = LabelHelper::createLabelMap(descriptor.labels, observation.labelValues);

        counters[descriptor.name].Add(labels).increment(observation.value);
    }
}
