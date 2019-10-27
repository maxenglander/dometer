#pragma once

#include "dns/server/event_type.hpp"

namespace Dometer::Dns::Server {
    class Event {
        public:
            virtual EventType getType() const = 0;
    };
}
