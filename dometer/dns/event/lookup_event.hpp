#pragma once

#include <chrono>

#include "dometer/dns/event/event.hpp"
#include "dometer/dns/event/event_type.hpp"
#include "dometer/dns/resolver/error.hpp"
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
                    const dns::message::Message& query,
                    const std::x::expected<dns::message::Message, dometer::dns::resolver::Error>& reply,
                    const std::chrono::microseconds duration);
            const std::chrono::microseconds getDuration() const;
            const dns::message::Message& getQuery() const;
            const std::x::expected<dns::message::Message, dometer::dns::resolver::Error>& getReply() const;
            EventType getType() const;
        private:
            const dns::message::Message& query;
            const std::x::expected<dns::message::Message, dometer::dns::resolver::Error>& reply;
            const std::chrono::microseconds duration;
    };
}
