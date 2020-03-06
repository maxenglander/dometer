#pragma once

#include "dometer/dns/event/parse_message_event.hpp"
#include "dometer/dns/message/message.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace dometer::dns::event {
    class parse_reply_event : public parse_message_event {
        public:
            parse_reply_event(uint64_t, const std::x::expected<dometer::dns::message::message, dometer::util::error>);
            parse_reply_event(const parse_reply_event&);
    };
}
