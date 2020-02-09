#include "dns/packet.hpp"
#include "dns/server/event_type.hpp"
#include "dns/server/lookup_event.hpp"
#include "x/expected.hpp"
#include "util/error.hpp"

using namespace dometer::util;
using namespace std::x;

namespace dometer::dns::server {
    LookupEvent::LookupEvent(
            const Packet& query,
            const expected<Packet, Error>& reply,
            const std::chrono::microseconds duration)
        :   query(query), reply(reply), duration(duration) {}

    const std::chrono::microseconds LookupEvent::getDuration() const {
        return duration;
    }

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
