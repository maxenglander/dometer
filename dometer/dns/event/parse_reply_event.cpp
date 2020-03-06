#include "dometer/dns/event/event_type.hpp"
#include "dometer/dns/event/parse_message_event.hpp"
#include "dometer/dns/event/parse_reply_event.hpp"
#include "dometer/dns/message/message.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::dns::event {
    ParseReplyEvent::ParseReplyEvent(const uint64_t sessionId,
            const std::x::expected<dns::message::Message, util::error> message)
        : ParseMessageEvent(sessionId, message) {}

    ParseReplyEvent::ParseReplyEvent(const ParseReplyEvent& event)
        : ParseReplyEvent(event.getSessionId(), event.getMessage())
    {}
}
