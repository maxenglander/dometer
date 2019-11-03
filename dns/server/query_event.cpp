#include "dns/packet.hpp"
#include "dns/server/event_type.hpp"
#include "dns/server/query_event.hpp"
#include "experimental/expected.hpp"
#include "util/error.hpp"

using namespace dometer::util;
using namespace std::experimental;

namespace dometer::dns::server {
    QueryEvent::QueryEvent(const expected<Packet, Error>& query) : query(query) {}

    const expected<Packet, Error>& QueryEvent::getQuery() const {
        return query;
    }

    EventType QueryEvent::getType() const {
        return EventType::QUERY;
    }
}
