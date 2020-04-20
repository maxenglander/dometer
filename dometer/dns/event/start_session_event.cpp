#include "dometer/dns/event/start_session_event.hpp"

namespace dometer::dns::event {
    start_session_event::start_session_event(const uint64_t session_id)
        : session_id(session_id)
    {}

    start_session_event::start_session_event(const start_session_event& src)
        : session_id(src.session_id)
    {}

    const uint64_t start_session_event::get_session_id() const {
        return session_id;
    }
}
