#include "dometer/dns/event/parse_message_event.hpp"
#include "dometer/dns/event/resolve_query_event.hpp"
#include "dometer/dns/event/session.hpp"
#include "std/x/optional.hpp"

namespace dometer::dns::event {
    Session::Session(uint64_t sessionId) : sessionId(sessionId) {}

    std::x::optional<ParseMessageEvent> Session::getParseQueryEvent() {
        return parseQueryEvent;
    }

    std::x::optional<ParseMessageEvent> Session::getParseReplyEvent() {
        return parseReplyEvent;
    }

    std::x::optional<ResolveQueryEvent> Session::getResolveQueryEvent() {
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
