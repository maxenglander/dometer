#include "dometer/dns/event/event_type.hpp"
#include "dometer/dns/event/parse_message_event.hpp"
#include "dometer/dns/message/message.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::dns::event {
    ParseMessageEvent::ParseMessageEvent(const uint64_t sessionId,
            const std::x::expected<dns::message::Message, util::Error> message)
        : sessionId(sessionId), message(message) {}

    ParseMessageEvent::ParseMessageEvent(const ParseMessageEvent& parseMessageEvent)
    : ParseMessageEvent(parseMessageEvent.getSessionId(),
                        parseMessageEvent.getMessage())
    {
    }

    const std::x::expected<dometer::dns::message::Message, util::Error>& ParseMessageEvent::getMessage() const {
        return message;
    }

    const uint64_t ParseMessageEvent::getSessionId() const {
        return sessionId;
    }

    EventType ParseMessageEvent::getType() const {
        return EventType::PARSE_MESSAGE;
    }
}
