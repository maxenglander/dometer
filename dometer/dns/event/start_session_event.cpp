#include "dometer/dns/event/event_type.hpp"
#include "dometer/dns/event/start_session_event.hpp"

namespace dometer::dns::event {
    StartSessionEvent::StartSessionEvent(const uint64_t sessionId)
        : sessionId(sessionId) {}

    const uint64_t StartSessionEvent::getSessionId() const {
        return sessionId;
    }

    EventType StartSessionEvent::getType() const {
        return EventType::START_SESSION;
    }
}
