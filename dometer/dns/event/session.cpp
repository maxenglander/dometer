#include <iostream>

#include "dometer/dns/event/parse_message_event.hpp"
#include "dometer/dns/event/resolve_query_event.hpp"
#include "dometer/dns/event/session.hpp"
#include "std/x/optional.hpp"

namespace dometer::dns::event {
    Session::Session(uint64_t sessionId) : sessionId(sessionId) {}

    Session::Session(const Session& session)
        : Session(session.getSessionId())
    {
        if(session.getParseQueryEvent()) {
            setParseQueryEvent(session.getParseQueryEvent().value());
        }
        if(session.getParseReplyEvent()) {
            setParseReplyEvent(session.getParseReplyEvent().value());
        }
        if(session.getResolveQueryEvent()) {
            setResolveQueryEvent(session.getResolveQueryEvent().value());
        }
    }

    Session::~Session() {
    }

    const uint64_t Session::getSessionId() const {
        return sessionId;
    }

    std::x::optional<parse_message_event> Session::getParseQueryEvent() const {
        return parseQueryEvent;
    }

    std::x::optional<parse_message_event> Session::getParseReplyEvent() const {
        return parseReplyEvent;
    }

    std::x::optional<resolve_query_event> Session::getResolveQueryEvent() const {
        return resolveQueryEvent;
    }

    void Session::setParseQueryEvent(parse_message_event parseQueryEvent) {
        this->parseQueryEvent.emplace(parseQueryEvent);
    }

    void Session::setParseReplyEvent(parse_message_event parseReplyEvent) {
        this->parseReplyEvent.emplace(parseReplyEvent);
    }

    void Session::setResolveQueryEvent(resolve_query_event resolveQueryEvent) {
        this->resolveQueryEvent.emplace(resolveQueryEvent);
    }
}
