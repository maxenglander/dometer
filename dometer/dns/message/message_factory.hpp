#pragma once

#include <memory>
#include <string>
#include <stdint.h>

#include "dometer/dns/record/class.hpp"
#include "dometer/dns/record/type.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::dns::message {
    class message;

    class message_factory {
        public:
            static message copy_message(const message& message);
            static message format_error(const message& query); 
            static std::x::expected<message, util::error> make_query(
                std::string, dometer::dns::record::type, dometer::dns::record::class_
            );
            static std::x::expected<message, util::error> make_reply(
                std::string, dometer::dns::record::type, dometer::dns::record::class_, uint16_t, std::string
            );
            static message not_implemented(const message& query); 
            static message nxdomain(const message& query); 
            static message server_failure(const message& query); 
    };
}
