#pragma once

#include "dometer/metrics/label.hpp"

namespace dometer::metrics {
    struct StringLabel : Label<std::string> {
        StringLabel() = delete;
        StringLabel(std::string name);
        std::string toString(std::string value) const;
    };
}
