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
    class ReplyEvent : public Event {
        public:
            ReplyEvent(
                    const expected<Dns::Packet, Util::Error>& query,
                    const expected<Packet, Util::Error>& reply);
            const expected<Dns::Packet, Util::Error>& getQuery() const;
            const expected<Dns::Packet, Util::Error>& getReply() const;
            EventType getType() const;
        private:
            const expected<Dns::Packet, Util::Error>& query;
            const expected<Dns::Packet, Util::Error>& reply;
    };
}
