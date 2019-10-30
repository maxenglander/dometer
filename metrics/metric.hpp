#pragma once

#include <memory>
#include <string>
#include <tuple>

#include "metrics/label.hpp"
#include "metrics/type.hpp"
#include "metrics/unit.hpp"

namespace Dometer::Metrics {
    template<typename V, typename... L>
    struct Metric {
        Metric(std::string, std::string, std::tuple<std::shared_ptr<Label<L>>...>, Type, Unit);
        const std::string name;
        const std::string description;
        const std::tuple<std::shared_ptr<Label<L>>...> labels;
        const Type type;
        const Unit unit;
    };
}

#include "metrics/metric.ipp"
