#include "dometer/dns/event/event_type.hpp"
#include "dometer/dns/event/parse_message_event.hpp"
#include "dometer/dns/event/parse_query_event.hpp"
#include "dometer/dns/message/message.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::dns::event {
    ParseQueryEvent::ParseQueryEvent(const uint64_t sessionId,
            const std::x::expected<dns::message::Message, util::Error> message)
        : ParseMessageEvent(sessionId, message) {}

    ParseQueryEvent::ParseQueryEvent(const ParseQueryEvent& event)
        : ParseQueryEvent(event.getSessionId(), event.getMessage())
    {}
}
