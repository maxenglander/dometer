#include "dometer/dns/event/parse_message_event.hpp"
#include "dometer/dns/event/parse_query_event.hpp"
#include "dometer/dns/message/message.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::dns::event {
    parse_query_event::parse_query_event(const uint64_t session_id,
            const std::x::expected<dns::message::message, util::error> message)
        : parse_message_event(session_id, message) {}

    parse_query_event::parse_query_event(const parse_query_event& event)
        : parse_query_event(event.get_session_id(), event.get_message())
    {}
}
