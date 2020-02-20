#pragma once

#include "dns/event/event_type.hpp"

namespace dometer::dns::event {
    class Event {
        public:
            virtual EventType getType() const = 0;
    };
}
