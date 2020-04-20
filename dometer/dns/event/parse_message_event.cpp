#include "dometer/dns/event/parse_message_event.hpp"
#include "dometer/dns/message/message.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::dns::event {
    parse_message_event::parse_message_event(const uint64_t session_id,
            const std::x::expected<dns::message::message, util::error> message)
        : session_id(session_id), message(message) {}

    parse_message_event::parse_message_event(const parse_message_event& _parse_message_event)
        : parse_message_event(_parse_message_event.get_session_id(), _parse_message_event.get_message())
    {
    }

    const std::x::expected<dometer::dns::message::message, util::error>& parse_message_event::get_message() const {
        return message;
    }

    const uint64_t parse_message_event::get_session_id() const {
        return session_id;
    }
}
