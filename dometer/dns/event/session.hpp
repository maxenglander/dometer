#pragma once

#include "dometer/dns/event/parse_message_event.hpp"
#include "dometer/dns/event/resolve_query_event.hpp"
#include "std/x/optional.hpp"

namespace dometer::dns::event {
    class Session {
        public:
            Session(uint64_t sessionId);
            std::x::optional<ParseMessageEvent> getParseQueryEvent();
            std::x::optional<ParseMessageEvent> getParseReplyEvent();
            std::x::optional<ResolveQueryEvent> getResolveQueryEvent();
            void setParseQueryEvent(ParseMessageEvent);
            void setParseReplyEvent(ParseMessageEvent);
            void setResolveQueryEvent(ResolveQueryEvent);
        private:
            const uint64_t sessionId;
            std::x::optional<ParseMessageEvent> parseQueryEvent;
            std::x::optional<ParseMessageEvent> parseReplyEvent;
            std::x::optional<ResolveQueryEvent> resolveQueryEvent;
    };
}
