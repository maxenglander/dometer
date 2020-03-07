#pragma once

#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include "dometer/metrics/label.hpp"
#include "dometer/metrics/metric.hpp"
#include "dometer/metrics/unit.hpp"

namespace dometer::metrics {
    template<typename... L>
    struct summary : metric<double, L...> {
        summary(std::string, std::string, std::tuple<std::shared_ptr<label<L>>...>,
                std::vector<double> quantiles, dometer::metrics::unit unit);
        const std::vector<double> quantiles;
    };
}

#include "dometer/metrics/summary.ipp"
