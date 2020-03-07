#include <string>

#include "dometer/metrics/string_label.hpp"

namespace dometer::metrics {
    string_label::string_label(std::string name) : label::label(name, "-") {}

    std::string string_label::to_string(std::string value) const {
        return value;
    }
}
