#pragma once

#include "dometer/dns/event/parse_query_event.hpp"
#include "dometer/dns/event/parse_reply_event.hpp"
#include "dometer/dns/event/resolve_query_event.hpp"
#include "dometer/dns/event/start_session_event.hpp"
#include "dometer/dns/event/stop_session_event.hpp"
#include "std/x/variant.hpp"

namespace dometer::dns::event {
    using any_event = std::x::variant<parse_query_event, parse_reply_event, resolve_query_event, start_session_event, stop_session_event>;
}
