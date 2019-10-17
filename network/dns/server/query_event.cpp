#include "experimental/expected.hpp"
#include "network/dns/packet.hpp"
#include "network/dns/server/event_type.hpp"
#include "network/dns/server/query_event.hpp"
#include "util/error.hpp"

using namespace Dometer::Util;
using namespace std::experimental;

namespace Dometer::Network::Dns::Server {
    QueryEvent::QueryEvent(const expected<Packet, Error>& query) : query(query) {}

    const expected<Packet, Error>& QueryEvent::getQuery() const {
        return query;
    }

    EventType QueryEvent::getType() const {
        return EventType::QUERY;
    }
}
