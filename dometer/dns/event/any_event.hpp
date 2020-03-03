#pragma once

#include "dometer/dns/event/parse_message_event.hpp"
#include "dometer/dns/event/resolve_query_event.hpp"
#include "dometer/dns/event/start_session_event.hpp"
#include "dometer/dns/event/stop_session_event.hpp"
#include "std/x/variant.hpp"

namespace dometer::dns::event {
    using AnyEvent = std::x::variant<ParseMessageEvent, ResolveQueryEvent, StartSessionEvent, StopSessionEvent>;
}
