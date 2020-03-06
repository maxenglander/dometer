#pragma once

#include "dometer/metrics/label.hpp"

namespace dometer::metrics {
    struct StringLabel : label<std::string> {
        StringLabel() = delete;
        StringLabel(std::string name);
        std::string to_string(std::string value) const;
    };
}
