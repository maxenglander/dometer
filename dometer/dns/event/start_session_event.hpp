#pragma once

#include <stdint.h>

namespace dometer::dns::event {
    class start_session_event {
        public:
            start_session_event(const uint64_t session_id);
            start_session_event(const start_session_event&);
            const uint64_t get_session_id() const;
        private:
            const uint64_t session_id;
    };
}
