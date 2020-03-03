#pragma once

#include "dometer/dns/event/event.hpp"
#include "dometer/dns/event/event_type.hpp"

namespace dometer::dns::event {
    class StartSessionEvent : public Event {
        public:
            StartSessionEvent(const uint64_t sessionId);
            const uint64_t getSessionId() const;
            EventType getType() const;
        private:
            const uint64_t sessionId;
    };
}
