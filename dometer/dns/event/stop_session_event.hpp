#pragma once

#include <stdint.h>

namespace dometer::dns::event {
    class stop_session_event {
        public:
            stop_session_event(const uint64_t session_id);
            const uint64_t get_session_id() const;
        private:
            const uint64_t session_id;
    };
}
