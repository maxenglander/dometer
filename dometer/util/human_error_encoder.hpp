#pragma once

#include <string>
#include <vector>

#include "dometer/util/error.hpp"
#include "dometer/util/error_encoder.hpp"

namespace dometer::util {
    class HumanErrorEncoder : public ErrorEncoder {
        public:
          std::string encode(Error);
        private:
          std::string encode(Error, size_t);
          std::string indent(size_t);
    };
}
