#pragma once

#include <memory>
#include <stdint.h>
#include <vector>

#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::dns::message {
    class Message;

    class Parser {
        public:
            static std::x::expected<Message, util::Error> parse(std::vector<uint8_t> bytes);
            static std::x::expected<Message, util::Error> parse(uint8_t *bytePtr, size_t size);
            static std::x::expected<Message, util::Error> parse(std::unique_ptr<uint8_t[]> bytes, size_t size);
    };
}
