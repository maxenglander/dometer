#include "dometer/metrics/boolean_label.hpp"

namespace dometer::metrics {
    boolean_label::boolean_label(std::string name) : label::label(name, false) {}

    std::string boolean_label::to_string(bool value) const {
        if(value)
            return std::string("true");
        return std::string("false");
    }
}
