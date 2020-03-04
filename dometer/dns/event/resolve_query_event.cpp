#include <vector>

#include "dometer/dns/question.hpp"
#include "dometer/dns/event/event_type.hpp"
#include "dometer/dns/event/resolve_query_event.hpp"
#include "dometer/dns/resolver/error.hpp"
#include "std/x/expected.hpp"

namespace dometer::dns::event {
    ResolveQueryEvent::ResolveQueryEvent(
            const uint64_t sessionId,
            const dometer::dns::Question question,
            const std::x::expected<std::vector<uint8_t>, dometer::dns::resolver::Error> resolution,
            const std::chrono::microseconds duration)
        :   sessionId(sessionId),
            question(question),
            resolution(resolution),
            duration(duration)
    {}

    const std::chrono::microseconds ResolveQueryEvent::getDuration() const {
        return duration;
    }

    const dometer::dns::Question& ResolveQueryEvent::getQuestion() const {
        return question;
    }

    const uint64_t ResolveQueryEvent::getSessionId() const {
        return sessionId;
    }

    const std::x::expected<std::vector<uint8_t>, dometer::dns::resolver::Error>& ResolveQueryEvent::getResolution() const {
        return resolution;
    }

    EventType ResolveQueryEvent::getType() const {
        return EventType::RESOLVE_QUERY;
    }
}
