#pragma once

#include <functional>
#include <iostream>
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
        std::cout << "prometheus: handling observation" << std::endl;
        switch(observation.descriptor.type) {
            case Type::COUNTER:
                handleCounter(observation);
        }
    }

    template<typename... T>
    void PrometheusHandler::handleCounter(Observation<T...> observation) {
        const Descriptor<T...>& descriptor = observation.descriptor;

        auto search = counters.find(descriptor.name);
        if(search == counters.end()) {
            counters.insert({descriptor.name, std::ref(prometheus::BuildCounter()
                .Name(descriptor.name)
                .Help(descriptor.description)
                .Register(*registry))});
            search = counters.find(descriptor.name);
        }

        std::map<std::string, std::string> labels
            = LabelHelper::createLabelMap(descriptor.labels, observation.labelValues);
        prometheus::Family<prometheus::Counter>& counter = search->second;
        counter.Add(labels).Increment(observation.value);
    }
}
