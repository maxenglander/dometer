#pragma once

#include <memory>
#include <string>
#include <tuple>

#include "metrics/label.hpp"
#include "metrics/metric.hpp"

namespace dometer::metrics {
    template<typename... L>
    struct Counter : Metric<uint64_t, L...> {
        Counter(std::string, std::string, std::tuple<std::shared_ptr<Label<L>>...>);
    };
}

#include "metrics/counter.ipp"
