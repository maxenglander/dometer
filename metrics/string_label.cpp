#include <string>

#include "metrics/string_label.hpp"

namespace dometer::metrics {
    StringLabel::StringLabel(std::string name) : Label::Label(name, "-") {}

    std::string StringLabel::toString(std::string value) const {
        return value;
    }
}
