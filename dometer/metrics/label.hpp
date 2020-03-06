#pragma once

#include <string>

namespace dometer::metrics {
    template<typename T>
    struct label {
        label() = delete;
        label(std::string name, T default_value) : name(name), default_value(default_value) {};
        virtual std::string to_string(T) const = 0;
        const std::string name;
        const T default_value;
    };
}
