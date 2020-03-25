#pragma once

#include <string>

#include "dometer/metrics/label.hpp"
#include "dometer/metrics/type.hpp"
#include "dometer/metrics/unit.hpp"

namespace dometer::metrics {
    struct metric {
        metric(std::string, std::string, dometer::metrics::type, unit);
        const std::string name;
        const std::string description;
        const dometer::metrics::type type;
        const dometer::metrics::unit unit;
    };
}
