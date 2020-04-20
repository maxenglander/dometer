#pragma once

#include <string>
#include <vector>

namespace dometer::util {
    class string_helper {
        public:
            static std::vector<std::string> split(char, std::string);
    };
}
