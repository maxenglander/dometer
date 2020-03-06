#pragma once

#include "dometer/dns/event/event.hpp"
#include "dometer/dns/event/event_type.hpp"
#include "dometer/dns/message/message.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::dns::event {
    class ParseMessageEvent : public Event {
        public:
            ParseMessageEvent(const uint64_t sessionId, const std::x::expected<dns::message::Message, util::error>);
            ParseMessageEvent(const ParseMessageEvent&);
            const std::x::expected<dometer::dns::message::Message, util::error>& getMessage() const;
            const uint64_t getSessionId() const;
            EventType getType() const;
        private:
            const uint64_t sessionId;
            const std::x::expected<dns::message::Message, util::error> message;
    };
}
