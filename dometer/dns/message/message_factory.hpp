#pragma once

#include <memory>
#include <stdint.h>

#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::dns::message {
    class message;

    class message_factory {
        public:
            static message copy_message(const message& message);
            static message format_error(const message& query); 
            static message not_implemented(const message& query); 
            static message server_failure(const message& query); 
    };
}
