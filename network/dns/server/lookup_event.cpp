#include "experimental/expected.hpp"
#include "network/dns/packet.hpp"
#include "network/dns/server/event_type.hpp"
#include "network/dns/server/lookup_event.hpp"
#include "util/error.hpp"

using namespace Dometer::Util;
using namespace std::experimental;

namespace Dometer::Network::Dns::Server {
    LookupEvent::LookupEvent(const Packet& query, const expected<Packet, Error>& reply)
        :   query(query), reply(reply) {}

    const expected<Packet, Error>& LookupEvent::getReply() const {
        return reply;
    }

    const Packet& LookupEvent::getQuery() const {
        return query;
    }

    EventType LookupEvent::getType() const {
        return EventType::LOOKUP;
    }
}
