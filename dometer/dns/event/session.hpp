#pragma once

#include "dometer/dns/event/parse_message_event.hpp"
#include "dometer/dns/event/resolve_query_event.hpp"
#include "std/x/optional.hpp"

namespace dometer::dns::event {
    class session {
        public:
            session(uint64_t session_id);
            session(const session&);

            const uint64_t get_session_id() const;
            std::x::optional<parse_message_event> get_parse_query_event() const;
            std::x::optional<parse_message_event> get_parse_reply_event() const;
            std::x::optional<resolve_query_event> get_resolve_query_event() const;
            void set_parse_query_event(parse_message_event);
            void set_parse_reply_event(parse_message_event);
            void set_resolve_query_event(resolve_query_event);
        private:
            const uint64_t session_id;
            std::x::optional<parse_message_event> _parse_query_event;
            std::x::optional<parse_message_event> _parse_reply_event;
            std::x::optional<resolve_query_event> _resolve_query_event;
    };
}
