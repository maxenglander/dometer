#include "dns/packet.hpp"
#include "dns/server/event_type.hpp"
#include "dns/server/lookup_event.hpp"
#include "experimental/expected.hpp"
#include "util/error.hpp"

using namespace Dometer::Util;
using namespace std::experimental;

namespace Dometer::Dns::Server {
    LookupEvent::LookupEvent(
            const Packet& query,
            const expected<Packet, Error>& reply)
        :   query(query), reply(reply) {}

    const Packet& LookupEvent::getQuery() const {
        return query;
    }

    const expected<Packet, Error>& LookupEvent::getReply() const {
        return reply;
    }

    EventType LookupEvent::getType() const {
        return EventType::LOOKUP;
    }
}
