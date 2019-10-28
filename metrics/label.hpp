#pragma once

#include <string>

namespace Dometer::Metrics {
    template<typename T>
    struct Label {
        Label() = delete;
        Label(std::string name, T defaultValue) : name(name), defaultValue(defaultValue) {};
        virtual std::string toString(T) const = 0;
        const std::string name;
        const T defaultValue;
    };
}
