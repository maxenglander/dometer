#pragma once

#include "network/dns/server/event_type.hpp"

namespace Dometer::Network::Dns::Server {
    class Event {
        public:
            virtual EventType getType() const = 0;
    };
}
