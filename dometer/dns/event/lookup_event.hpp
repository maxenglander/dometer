#pragma once

#include <chrono>

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
    class LookupEvent : public Event {
        public:
            LookupEvent(
                    const dns::Packet& query,
                    const std::x::expected<dns::Packet, util::Error>& reply,
                    const std::chrono::microseconds duration);
            const std::chrono::microseconds getDuration() const;
            const dns::Packet& getQuery() const;
            const std::x::expected<dns::Packet, util::Error>& getReply() const;
            EventType getType() const;
        private:
            const dns::Packet& query;
            const std::x::expected<dns::Packet, util::Error>& reply;
            const std::chrono::microseconds duration;
    };
}
