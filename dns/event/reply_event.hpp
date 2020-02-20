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
    class ReplyEvent : public Event {
        public:
            ReplyEvent(
                    const std::x::expected<dns::Packet, util::Error>& query,
                    const std::x::expected<dns::Packet, util::Error>& reply);
            const std::x::expected<dns::Packet, util::Error>& getQuery() const;
            const std::x::expected<dns::Packet, util::Error>& getReply() const;
            EventType getType() const;
        private:
            const std::x::expected<dns::Packet, util::Error>& query;
            const std::x::expected<dns::Packet, util::Error>& reply;
    };
}
