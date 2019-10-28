#pragma once

#include <memory>
#include <string>
#include <tuple>

#include "metrics/label.hpp"
#include "metrics/type.hpp"
#include "metrics/unit.hpp"

namespace Dometer::Metrics {
    template<typename... T>
    struct Descriptor {
        Descriptor(std::string, std::string, std::tuple<std::shared_ptr<Label<T>>...>, Type, Unit);
        const std::string name;
        const std::string description;
        const std::tuple<std::shared_ptr<Label<T>>...> labels;
        const Type type;
        const Unit unit;
    };
}

#include "metrics/descriptor.ipp"
