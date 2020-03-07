#pragma once

#include <memory>
#include <string>
#include <tuple>

#include "dometer/metrics/label.hpp"
#include "dometer/metrics/metric.hpp"

namespace dometer::metrics {
    template<typename... L>
    struct counter : metric<uint64_t, L...> {
        counter(std::string, std::string, std::tuple<std::shared_ptr<label<L>>...>);
    };
}

#include "dometer/metrics/counter.ipp"
