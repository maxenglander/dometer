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

    std::x::optional<ParseMessageEvent> Session::getParseQueryEvent() const {
        return parseQueryEvent;
    }

    std::x::optional<ParseMessageEvent> Session::getParseReplyEvent() const {
        return parseReplyEvent;
    }

    std::x::optional<ResolveQueryEvent> Session::getResolveQueryEvent() const {
        return resolveQueryEvent;
    }

    void Session::setParseQueryEvent(ParseMessageEvent parseQueryEvent) {
        this->parseQueryEvent.emplace(parseQueryEvent);
    }

    void Session::setParseReplyEvent(ParseMessageEvent parseReplyEvent) {
        this->parseReplyEvent.emplace(parseReplyEvent);
    }

    void Session::setResolveQueryEvent(ResolveQueryEvent resolveQueryEvent) {
        this->resolveQueryEvent.emplace(resolveQueryEvent);
    }
}
