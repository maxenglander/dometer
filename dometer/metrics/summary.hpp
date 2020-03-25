#pragma once

#include <string>
#include <vector>

#include "dometer/metrics/label.hpp"
#include "dometer/metrics/metric.hpp"
#include "dometer/metrics/unit.hpp"

namespace dometer::metrics {
    struct summary : metric {
        summary(std::string,
                std::string,
                std::vector<double> quantiles,
                dometer::metrics::unit _unit);
        const std::vector<double> quantiles;
    };
}
