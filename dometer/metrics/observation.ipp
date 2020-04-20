#pragma once

#include <map>

namespace dometer::metrics {
    template <typename T>
    observation<T>::observation(std::map<std::string, std::string> labels, T value)
        : labels(labels), value(value)
    {}
}
