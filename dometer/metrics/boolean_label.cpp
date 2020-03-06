#include "dometer/metrics/boolean_label.hpp"

namespace dometer::metrics {
    BooleanLabel::BooleanLabel(std::string name) : label::label(name, false) {}

    std::string BooleanLabel::to_string(bool value) const {
        if(value)
            return std::string("true");
        return std::string("false");
    }
}
