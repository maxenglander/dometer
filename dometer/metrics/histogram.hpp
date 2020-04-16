#pragma once

#include <string>
#include <vector>

#include "dometer/metrics/label.hpp"
#include "dometer/metrics/metric.hpp"
#include "dometer/metrics/unit.hpp"

namespace dometer::metrics {
    struct histogram : metric {
        histogram(std::string,
                  std::string,
                  std::vector<double> buckets,
                  dometer::metrics::unit _unit);
        const std::vector<double> buckets;
    };
}
