#include "experimental/expected.hpp"
#include "network/dns/packet.hpp"
#include "network/dns/server/event_type.hpp"
#include "network/dns/server/reply_event.hpp"
#include "util/error.hpp"

using namespace Dometer::Util;
using namespace std::experimental;

namespace Dometer::Network::Dns::Server {
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
