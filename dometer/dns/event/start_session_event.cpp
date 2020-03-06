#include "dometer/dns/event/start_session_event.hpp"

namespace dometer::dns::event {
    start_session_event::start_session_event(const uint64_t sessionId)
        : sessionId(sessionId) {}

    const uint64_t start_session_event::getSessionId() const {
        return sessionId;
    }
}
