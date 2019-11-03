#pragma once

#include "dns/server/event.hpp"
#include "dns/server/event_type.hpp"
#include "experimental/expected.hpp"
#include "util/error.hpp"

namespace dometer::dns {
    class Packet;
}

namespace Dns = dometer::dns;
namespace util = dometer::util;
using namespace std::experimental;

namespace dometer::dns::server {
    class ReplyEvent : public Event {
        public:
            ReplyEvent(
                    const expected<dns::Packet, util::Error>& query,
                    const expected<Packet, util::Error>& reply);
            const expected<dns::Packet, util::Error>& getQuery() const;
            const expected<dns::Packet, util::Error>& getReply() const;
            EventType getType() const;
        private:
            const expected<dns::Packet, util::Error>& query;
            const expected<dns::Packet, util::Error>& reply;
    };
}
