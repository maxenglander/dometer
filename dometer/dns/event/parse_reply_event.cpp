#include "dometer/dns/event/parse_message_event.hpp"
#include "dometer/dns/event/parse_reply_event.hpp"
#include "dometer/dns/message/message.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::dns::event {
    parse_reply_event::parse_reply_event(const uint64_t session_id,
            const std::x::expected<dns::message::message, util::error> message)
        : parse_message_event(session_id, message) {}

    parse_reply_event::parse_reply_event(const parse_reply_event& event)
        : parse_reply_event(event.get_session_id(), event.get_message())
    {}
}
