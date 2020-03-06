#pragma once

#include <string>

#include "dometer/metrics/label.hpp"

namespace dometer::metrics {
    struct BooleanLabel : label<bool> {
        BooleanLabel() = delete;
        BooleanLabel(std::string);
        std::string to_string(bool value) const;
    };
}
