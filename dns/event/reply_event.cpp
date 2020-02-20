#include "dns/packet.hpp"
#include "dns/event/event_type.hpp"
#include "dns/event/reply_event.hpp"
#include "util/error.hpp"
#include "x/expected.hpp"

namespace dns = dometer::dns;
namespace util = dometer::util;

namespace dometer::dns::event {
    ReplyEvent::ReplyEvent(
                const std::x::expected<dns::Packet, util::Error>& query,
                const std::x::expected<dns::Packet, util::Error>& reply)
        :   query(query), reply(reply) {}

    const std::x::expected<dns::Packet, util::Error>& ReplyEvent::getQuery() const {
        return query;
    }

    const std::x::expected<dns::Packet, util::Error>& ReplyEvent::getReply() const {
        return reply;
    }

    EventType ReplyEvent::getType() const {
        return EventType::REPLY;
    }
}
