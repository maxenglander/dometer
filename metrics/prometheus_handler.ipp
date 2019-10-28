#pragma once

#include <string>
#include <tuple>
#include <unordered_map>

#include "metrics/descriptor.hpp"
#include "metrics/observation.hpp"
#include "metrics/prometheus_handler.hpp"

#include "prometheus/counter.h"

#include "util/tuple_helper.hpp"

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

        std::unordered_map<std::string, std::string> labels;

        for(int i = 0; i < sizeof...(T); i++) {
            labels.emplace(TupleHelper::applyAt(descriptor.labels, i, [&observation, i](auto label) {
                TupleHelper::applyAt(observation.labelValues, i, [&label](auto value) {
                    return std::make_pair(label.name, label.toString(value));
                });
            }));
        }
    }
}
