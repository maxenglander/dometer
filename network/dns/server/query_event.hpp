#pragma once

#include "experimental/expected.hpp"
#include "network/dns/server/event.hpp"
#include "network/dns/server/event_type.hpp"
#include "util/error.hpp"

namespace Dometer::Network::Dns {
    class Packet;
}

namespace Util = Dometer::Util;
using namespace std::experimental;

namespace Dometer::Network::Dns::Server {
    class QueryEvent : public Event {
        public:
            QueryEvent(const expected<Dns::Packet, Util::Error>&);
            const expected<Dns::Packet, Util::Error>& getQuery() const;
            EventType getType() const;
        private:
            const expected<Dns::Packet, Util::Error>& query;
    };
}
