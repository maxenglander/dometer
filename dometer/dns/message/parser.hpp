#pragma once

#include <memory>
#include <stdint.h>
#include <vector>

#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::dns::message {
    class message;

    class parser {
        public:
            static std::x::expected<message, util::error> parse(std::vector<uint8_t> bytes);
            static std::x::expected<message, util::error> parse(uint8_t *bytePtr, size_t size);
            static std::x::expected<message, util::error> parse(std::unique_ptr<uint8_t[]> bytes, size_t size);
    };
}
