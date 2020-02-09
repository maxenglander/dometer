#pragma once

#include "dns/server/event.hpp"
#include "dns/server/event_type.hpp"
#include "x/expected.hpp"
#include "util/error.hpp"

namespace dometer::dns {
    class Packet;
}

namespace util = dometer::util;
using namespace std::x;

namespace dometer::dns::server {
    class QueryEvent : public Event {
        public:
            QueryEvent(const expected<dns::Packet, util::Error>&);
            const expected<dns::Packet, util::Error>& getQuery() const;
            EventType getType() const;
        private:
            const expected<dns::Packet, util::Error>& query;
    };
}
