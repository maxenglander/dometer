#pragma once

#include <string>

namespace Dometer::Metrics {
    template<typename T>
    struct Label {
        Label() = delete;
        Label(std::string);
        virtual std::string toString(T) const = 0;
        const std::string name;
    };
}
