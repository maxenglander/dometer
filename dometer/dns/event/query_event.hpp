#pragma once

#include "dometer/dns/event/event.hpp"
#include "dometer/dns/event/event_type.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace dometer::dns {
    class Packet;
}

namespace dns = dometer::dns;
namespace util = dometer::util;

namespace dometer::dns::event {
    class QueryEvent : public Event {
        public:
            QueryEvent(const std::x::expected<dns::Packet, util::Error>&);
            const std::x::expected<dns::Packet, util::Error>& getQuery() const;
            EventType getType() const;
        private:
            const std::x::expected<dns::Packet, util::Error>& query;
    };
}
