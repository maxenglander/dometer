#pragma once

#include "dometer/metrics/label.hpp"

namespace dometer::metrics {
    struct string_label : label<std::string> {
        string_label() = delete;
        string_label(std::string name);
        std::string to_string(std::string value) const;
    };
}
