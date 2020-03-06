#pragma once

#include <memory>
#include <stdint.h>

#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::dns::message {
    class message;

    class MessageFactory {
        public:
            static message copyMessage(const message& message);
            static message formaterror(const message& query); 
            static message notImplemented(const message& query); 
            static message serverFailure(const message& query); 
    };
}
