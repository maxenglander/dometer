#pragma once

#include <string>

#include "std/x/optional.hpp"

namespace dometer::main {
    struct Options {
        std::x::optional<std::string> config;
        bool help;
    };
}
