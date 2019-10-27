#include "dns/packet.hpp"
#include "dns/server/event_type.hpp"
#include "dns/server/reply_event.hpp"
#include "experimental/expected.hpp"
#include "util/error.hpp"

using namespace Dometer::Util;
using namespace std::experimental;

namespace Dometer::Dns::Server {
    ReplyEvent::ReplyEvent(
                const expected<Packet, Error>& query,
                const expected<Packet, Error>& reply)
        :   query(query), reply(reply) {}

    const expected<Packet, Error>& ReplyEvent::getQuery() const {
        return query;
    }

    const expected<Packet, Error>& ReplyEvent::getReply() const {
        return reply;
    }

    EventType ReplyEvent::getType() const {
        return EventType::REPLY;
    }
}
