#pragma once

#include <string>
#include <vector>

namespace dometer::util {
    class StringHelper {
        public:
            static std::vector<std::string> split(char, std::string);
    };
}
