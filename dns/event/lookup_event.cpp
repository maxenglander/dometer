#include "dns/packet.hpp"
#include "dns/event/event_type.hpp"
#include "dns/event/lookup_event.hpp"
#include "util/error.hpp"
#include "x/expected.hpp"

namespace dns = dometer::dns;
namespace util = dometer::util;

namespace dometer::dns::event {
    LookupEvent::LookupEvent(
            const dns::Packet& query,
            const std::x::expected<dns::Packet, util::Error>& reply,
            const std::chrono::microseconds duration)
        :   query(query), reply(reply), duration(duration) {}

    const std::chrono::microseconds LookupEvent::getDuration() const {
        return duration;
    }

    const dns::Packet& LookupEvent::getQuery() const {
        return query;
    }

    const std::x::expected<dns::Packet, util::Error>& LookupEvent::getReply() const {
        return reply;
    }

    EventType LookupEvent::getType() const {
        return EventType::LOOKUP;
    }
}
