#include "metrics/boolean_label.hpp"

namespace dometer::metrics {
    BooleanLabel::BooleanLabel(std::string name) : Label::Label(name, false) {}

    std::string BooleanLabel::toString(bool value) const {
        if(value)
            return std::string("true");
        return std::string("false");
    }
}
