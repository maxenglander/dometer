#pragma once

#include "dometer/dns/event/parse_message_event.hpp"
#include "dometer/dns/message/message.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace dometer::dns::event {
    class ParseReplyEvent : public ParseMessageEvent {
        public:
            ParseReplyEvent(uint64_t, const std::x::expected<dometer::dns::message::Message, dometer::util::Error>);
            ParseReplyEvent(const ParseReplyEvent&);
    };
}
