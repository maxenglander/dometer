#pragma once

#include "metrics/label.hpp"

namespace Dometer::Metrics {
    struct StringLabel : Label<std::string> {
        StringLabel() = delete;
        StringLabel(std::string name);
        std::string toString(std::string value) const;
    };
}
