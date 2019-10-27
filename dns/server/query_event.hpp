#pragma once

#include "dns/server/event.hpp"
#include "dns/server/event_type.hpp"
#include "experimental/expected.hpp"
#include "util/error.hpp"

namespace Dometer::Dns {
    class Packet;
}

namespace Util = Dometer::Util;
using namespace std::experimental;

namespace Dometer::Dns::Server {
    class QueryEvent : public Event {
        public:
            QueryEvent(const expected<Dns::Packet, Util::Error>&);
            const expected<Dns::Packet, Util::Error>& getQuery() const;
            EventType getType() const;
        private:
            const expected<Dns::Packet, Util::Error>& query;
    };
}
