#pragma once

#include <string>

namespace dometer::util {
    struct Error {
        const std::string message;
        const int number;
    };
}
