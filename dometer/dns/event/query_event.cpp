#include "dometer/dns/message/message.hpp"
#include "dometer/dns/event/event_type.hpp"
#include "dometer/dns/event/query_event.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace dns = dometer::dns;
namespace util = dometer::util;

namespace dometer::dns::event {
    QueryEvent::QueryEvent(const std::x::expected<dns::message::Message, util::Error>& query) : query(query) {}

    const std::x::expected<dns::message::Message, util::Error>& QueryEvent::getQuery() const {
        return query;
    }

    EventType QueryEvent::getType() const {
        return EventType::QUERY;
    }
}
