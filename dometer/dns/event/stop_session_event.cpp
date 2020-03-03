#include "dometer/dns/event/event_type.hpp"
#include "dometer/dns/event/stop_session_event.hpp"

namespace dometer::dns::event {
    StopSessionEvent::StopSessionEvent(const uint64_t sessionId)
        : sessionId(sessionId) {}

    const uint64_t StopSessionEvent::getSessionId() const {
        return sessionId;
    }

    EventType StopSessionEvent::getType() const {
        return EventType::STOP_SESSION;
    }
}
