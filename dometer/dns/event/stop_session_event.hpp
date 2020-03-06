#pragma once

#include <stdint.h>

namespace dometer::dns::event {
    class stop_session_event {
        public:
            stop_session_event(const uint64_t sessionId);
            const uint64_t getSessionId() const;
        private:
            const uint64_t sessionId;
    };
}
