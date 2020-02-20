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
    struct Summary : Metric<double, L...> {
        Summary(std::string, std::string, std::tuple<std::shared_ptr<Label<L>>...>,
                std::vector<double> quantiles, dometer::metrics::Unit unit);
        const std::vector<double> quantiles;
    };
}

#include "dometer/metrics/summary.ipp"
