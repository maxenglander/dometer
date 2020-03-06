#include "dometer/dns/event/stop_session_event.hpp"

namespace dometer::dns::event {
    stop_session_event::stop_session_event(const uint64_t session_id)
        : session_id(session_id) {}

    const uint64_t stop_session_event::get_session_id() const {
        return session_id;
    }
}
