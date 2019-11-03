#pragma once

#include <chrono>

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
    class LookupEvent : public Event {
        public:
            LookupEvent(
                    const dns::Packet& query,
                    const expected<dns::Packet, util::Error>& reply,
                    const std::chrono::microseconds duration);
            const std::chrono::microseconds getDuration() const;
            const dns::Packet& getQuery() const;
            const expected<dns::Packet, util::Error>& getReply() const;
            EventType getType() const;
        private:
            const dns::Packet& query;
            const expected<dns::Packet, util::Error>& reply;
            const std::chrono::microseconds duration;
    };
}
