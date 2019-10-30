#pragma once

#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include "metrics/label.hpp"
#include "metrics/metric.hpp"
#include "metrics/unit.hpp"

namespace Dometer::Metrics {
    template<typename... L>
    struct Summary : Metric<double, L...> {
        Summary(std::string, std::string, std::tuple<std::shared_ptr<Label<L>>...>,
                std::vector<double> quantiles, Dometer::Metrics::Unit unit);
        const std::vector<double> quantiles;
    };
}

#include "metrics/summary.ipp"
