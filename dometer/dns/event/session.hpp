#pragma once

#include "dometer/dns/event/parse_message_event.hpp"
#include "dometer/dns/event/resolve_query_event.hpp"
#include "std/x/optional.hpp"

namespace dometer::dns::event {
    class Session {
        public:
            Session(uint64_t sessionId);
            Session(const Session&);
            ~Session();

            const uint64_t getSessionId() const;
            std::x::optional<parse_message_event> getParseQueryEvent() const;
            std::x::optional<parse_message_event> getParseReplyEvent() const;
            std::x::optional<resolve_query_event> getResolveQueryEvent() const;
            void setParseQueryEvent(parse_message_event);
            void setParseReplyEvent(parse_message_event);
            void setResolveQueryEvent(resolve_query_event);
        private:
            const uint64_t sessionId;
            std::x::optional<parse_message_event> parseQueryEvent;
            std::x::optional<parse_message_event> parseReplyEvent;
            std::x::optional<resolve_query_event> resolveQueryEvent;
    };
}
