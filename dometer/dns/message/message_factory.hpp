#pragma once

#include <memory>
#include <stdint.h>

#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::dns::message {
    class Message;

    class MessageFactory {
        public:
            static Message copyMessage(const Message& message);

            static std::x::expected<Message, util::Error> makeMessage(uint8_t *bytePtr, size_t size);
            static std::x::expected<Message, util::Error> makeMessage(std::unique_ptr<uint8_t[]> bytes, size_t size);

            static Message formatError(const Message& query); 
            static Message notImplemented(const Message& query); 
            static Message serverFailure(const Message& query); 
    };
}
