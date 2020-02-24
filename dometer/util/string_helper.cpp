#include <string>
#include <vector>

#include "dometer/util/string_helper.hpp"

namespace dometer::util {
    std::vector<std::string> StringHelper::split(char delimiter, std::string string) {
        std::vector<std::string> results;

        std::size_t current, previous = 0;
        current = string.find(delimiter);
        while(current != std::string::npos) {
            results.push_back(string.substr(previous, current - previous));
            previous = current + 1;
            current = string.find(delimiter);
        }
        results.push_back(string.substr(previous, current - previous));
        return results;
    }
}
