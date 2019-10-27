#pragma once

#include <memory>
#include <string>
#include <tuple>

#include "metrics/label.hpp"
#include "metrics/unit.hpp"

namespace Dometer::Metrics {
    template<typename T...>
    struct Descriptor {
        const std::string name;
        const std::string description;
        const tuple<std::unique_ptr<Label<T>>...> labels;
        const Unit unit;
    };
}
