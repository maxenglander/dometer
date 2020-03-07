#pragma once

#include <string>

#include "dometer/metrics/label.hpp"

namespace dometer::metrics {
    struct boolean_label : label<bool> {
        boolean_label() = delete;
        boolean_label(std::string);
        std::string to_string(bool value) const;
    };
}
