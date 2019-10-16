#pragma once

#include "experimental/expected.hpp"
#include "network/dns/packet.hpp"
#include "network/dns/server/event.hpp"
#include "network/dns/server/event_type.hpp"
#include "util/error.hpp"

using namespace Dometer::Util;
using namespace std::experimental;

namespace Dometer::Network::Dns::Server {
    class LookupEvent : public Event {
        public:
            LookupEvent(const Packet&, const expected<Packet, Error>&);
            const Packet& getQuery() const;
            const expected<Packet, Error>& getReply() const;
            EventType getType() const;
        private:
            const Packet& query;
            const expected<Packet, Error>& reply;
    };
}
