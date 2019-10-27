#include "metrics/boolean_label.hpp"

namespace Dometer::Metrics {
    BooleanLabel::BooleanLabel(std::string name) : Label::Label(name) {}

    std::string BooleanLabel::toString(bool value) const {
        if(value)
            return "true";
        else
            return "false";
    }
}
