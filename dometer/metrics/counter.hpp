#pragma once

#include <string>
#include <vector>

#include "dometer/metrics/label.hpp"
#include "dometer/metrics/metric.hpp"

namespace dometer::metrics {
    struct counter : metric {
        counter(std::string, std::string, std::tuple<std::string>);
    };
}
