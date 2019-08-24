#pragma once

#include <string>

namespace DnsTelemeter::Util {
    struct Error {
        const std::string message;
        const int number;
    };
}
