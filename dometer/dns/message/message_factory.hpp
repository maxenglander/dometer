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
            static Message formatError(const Message& query); 
            static Message notImplemented(const Message& query); 
            static Message serverFailure(const Message& query); 
    };
}
