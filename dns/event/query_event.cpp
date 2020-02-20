#include "dns/packet.hpp"
#include "dns/event/event_type.hpp"
#include "dns/event/query_event.hpp"
#include "util/error.hpp"
#include "x/expected.hpp"

namespace dns = dometer::dns;
namespace util = dometer::util;

namespace dometer::dns::event {
    QueryEvent::QueryEvent(const std::x::expected<dns::Packet, util::Error>& query) : query(query) {}

    const std::x::expected<dns::Packet, util::Error>& QueryEvent::getQuery() const {
        return query;
    }

    EventType QueryEvent::getType() const {
        return EventType::QUERY;
    }
}
