#include <iostream>

#include "dometer/dns/event/parse_message_event.hpp"
#include "dometer/dns/event/resolve_query_event.hpp"
#include "dometer/dns/event/session.hpp"
#include "std/x/optional.hpp"

namespace dometer::dns::event {
    session::session(uint64_t session_id) : session_id(session_id) {}

    session::session(const session& _session)
        : session(_session.get_session_id())
    {
        if(_session.get_parse_query_event()) {
            set_parse_query_event(_session.get_parse_query_event().value());
        }
        if(_session.get_parse_reply_event()) {
            set_parse_reply_event(_session.get_parse_reply_event().value());
        }
        if(_session.get_resolve_query_event()) {
            set_resolve_query_event(_session.get_resolve_query_event().value());
        }
    }

    session::~session() {
    }

    const uint64_t session::get_session_id() const {
        return session_id;
    }

    std::x::optional<parse_message_event> session::get_parse_query_event() const {
        return _parse_query_event;
    }

    std::x::optional<parse_message_event> session::get_parse_reply_event() const {
        return _parse_reply_event;
    }

    std::x::optional<resolve_query_event> session::get_resolve_query_event() const {
        return _resolve_query_event;
    }

    void session::set_parse_query_event(parse_message_event _parse_query_event) {
        this->_parse_query_event.emplace(_parse_query_event);
    }

    void session::set_parse_reply_event(parse_message_event _parse_reply_event) {
        this->_parse_reply_event.emplace(_parse_reply_event);
    }

    void session::set_resolve_query_event(resolve_query_event _resolve_query_event) {
        this->_resolve_query_event.emplace(_resolve_query_event);
    }
}
