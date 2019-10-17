#pragma once

#include "experimental/expected.hpp"
#include "network/dns/server/event.hpp"
#include "network/dns/server/event_type.hpp"
#include "util/error.hpp"

namespace Dometer::Network::Dns {
    class Packet;
}

namespace Dns = Dometer::Network::Dns;
namespace Util = Dometer::Util;
using namespace std::experimental;

namespace Dometer::Network::Dns::Server {
    class LookupEvent : public Event {
        public:
            LookupEvent(
                    const Dns::Packet& query,
                    const expected<Dns::Packet, Util::Error>& reply);
            const Dns::Packet& getQuery() const;
            const expected<Dns::Packet, Util::Error>& getReply() const;
            EventType getType() const;
        private:
            const Dns::Packet& query;
            const expected<Dns::Packet, Util::Error>& reply;
    };
}
