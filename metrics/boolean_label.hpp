#pragma once

#include <string>

#include "metrics/label.hpp"

namespace dometer::metrics {
    struct BooleanLabel : Label<bool> {
        BooleanLabel() = delete;
        BooleanLabel(std::string);
        std::string toString(bool value) const;
    };
}
