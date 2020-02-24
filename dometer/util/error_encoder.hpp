#pragma once

#include <string>
#include <vector>

#include "dometer/util/error.hpp"

namespace dometer::util {
    class ErrorEncoder {
        public:
           virtual std::string encode(Error) = 0;
    };
}
