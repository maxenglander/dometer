#pragma once

#include <memory>
#include <string>
#include <tuple>

#include "metrics/label.hpp"
#include "metrics/metric.hpp"

namespace Dometer::Metrics {
    template<typename... T>
    struct Counter : Metric<T...> {
        Counter(std::string, std::string, std::tuple<std::shared_ptr<Label<T>>...>);
    };
}

#include "metrics/counter.ipp"
