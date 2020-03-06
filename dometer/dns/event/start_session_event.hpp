#pragma once

#include <stdint.h>

namespace dometer::dns::event {
    class start_session_event {
        public:
            start_session_event(const uint64_t sessionId);
            const uint64_t getSessionId() const;
        private:
            const uint64_t sessionId;
    };
}
