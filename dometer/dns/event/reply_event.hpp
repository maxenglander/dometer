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
    class ReplyEvent : public Event {
        public:
            ReplyEvent(
                    const std::x::expected<dns::message::Message, util::Error>& query,
                    const std::x::expected<dns::message::Message, util::Error>& reply);
            const std::x::expected<dns::message::Message, util::Error>& getQuery() const;
            const std::x::expected<dns::message::Message, util::Error>& getReply() const;
            EventType getType() const;
        private:
            const std::x::expected<dns::message::Message, util::Error>& query;
            const std::x::expected<dns::message::Message, util::Error>& reply;
    };
}
