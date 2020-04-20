#pragma once

#include <string>
#include <vector>

#include "dometer/util/error.hpp"
#include "dometer/util/error_encoder.hpp"

namespace dometer::util {
    class human_friendly_error_encoder : public error_encoder {
        public:
          std::string encode(error);
        private:
          std::string encode(error, size_t);
          std::string indent(size_t);
    };
}
