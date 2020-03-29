#pragma once

#include <string>

#include "dometer/metrics/metric.hpp"

namespace dometer::metrics {
    struct counter : metric {
        counter(std::string, std::string);
    };
}
