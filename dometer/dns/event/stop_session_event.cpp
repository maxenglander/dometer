#include "dometer/dns/event/stop_session_event.hpp"

namespace dometer::dns::event {
    stop_session_event::stop_session_event(const uint64_t sessionId)
        : sessionId(sessionId) {}

    const uint64_t stop_session_event::getSessionId() const {
        return sessionId;
    }
}
