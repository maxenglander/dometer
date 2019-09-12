#pragma once

#include <string>

namespace Dometer::Util {
    struct Error {
        const std::string message;
        const int number;
    };
}
