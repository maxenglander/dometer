#pragma once

#include <memory>
#include <string>
#include <tuple>

#include "dometer/metrics/label.hpp"
#include "dometer/metrics/type.hpp"
#include "dometer/metrics/unit.hpp"

namespace dometer::metrics {
    template<typename V, typename... L>
    struct Metric {
        Metric(std::string, std::string, std::tuple<std::shared_ptr<Label<L>>...>, dometer::metrics::type, Unit);
        const std::string name;
        const std::string description;
        const std::tuple<std::shared_ptr<Label<L>>...> labels;
        const dometer::metrics::type type;
        const Unit unit;
    };
}

#include "dometer/metrics/metric.ipp"
