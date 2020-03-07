#pragma once

#include <string>

namespace dometer::dns::resolver {
    enum class error_code {
        noerror = 0,
        connrefused = 1,
        msgsize = 2,
        parseerror = 3,
        timedout = 4,
        other = 255
    };
    
    std::string to_string(const error_code&);
}
