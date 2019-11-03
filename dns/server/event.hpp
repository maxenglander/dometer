#pragma once

#include "dns/server/event_type.hpp"

namespace dometer::dns::server {
    class Event {
        public:
            virtual EventType getType() const = 0;
    };
}
