#pragma once

#include "dns/event/event.hpp"
#include "dns/event/event_type.hpp"
#include "util/error.hpp"
#include "x/expected.hpp"

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
