#include <iostream>
#include <string>
#include <vector>

#include "dometer/util/error.hpp"
#include "dometer/util/human_friendly_error_encoder.hpp"

namespace dometer::util {
    std::string human_friendly_error_encoder::encode(error error) {
        std::size_t depth = 0;

        std::string result = encode(error, depth);

        std::shared_ptr<dometer::util::error> cause = error.cause;

        while(cause) {
            result += indent(depth) + "Why:\n";
            depth++;
            result += encode(*cause, depth);
            cause = cause->cause;
        }

        return result;
    }

    std::string human_friendly_error_encoder::encode(error error, std::size_t depth) {
        std::string result = indent(depth) + error.message + "\n";

        if(error.code != 0)
            result += indent(depth) + "Code: " + std::to_string(error.code) + "\n";

        if(error.details.size() > 0) {
            for(auto it = error.details.begin(); it < error.details.end(); it++)
                result += indent(depth) + "- " + *it + "\n";
        }

        return result;
    }

    std::string human_friendly_error_encoder::indent(std::size_t depth) {
        std::string result;
        for(size_t i = 0; i < depth; i++)
            result += "  ";
        return result;
    }
}
