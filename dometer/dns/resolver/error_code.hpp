#pragma once

#include <string>

namespace dometer::dns::resolver {
    enum class ErrorCode {
        NOERROR = 0,
        CONNREFUSED = 1,
        MSGSIZE = 2,
        PARSEERROR = 3,
        TIMEDOUT = 4,
        OTHER = 255
    };
    
    std::string to_string(const ErrorCode&);
}
