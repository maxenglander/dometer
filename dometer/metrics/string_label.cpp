#include <string>

#include "dometer/metrics/string_label.hpp"

namespace dometer::metrics {
    StringLabel::StringLabel(std::string name) : label::label(name, "-") {}

    std::string StringLabel::to_string(std::string value) const {
        return value;
    }
}
