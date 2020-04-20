#pragma once

#include <string>
#include <vector>

#include "dometer/util/error.hpp"

namespace dometer::util {
    class error_encoder {
        public:
           virtual std::string encode(error) = 0;
    };
}
