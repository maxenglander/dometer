#pragma once

#include <memory>
#include <string>
#include <tuple>

#include "metrics/descriptor.hpp"
#include "metrics/label.hpp"

namespace Dometer::Metrics {
    template<typename... T>
    struct CounterDescriptor : Descriptor<T...> {
        CounterDescriptor(std::string, std::string, std::tuple<std::shared_ptr<Label<T>>...>);
    };
}

#include "metrics/counter_descriptor.ipp"
