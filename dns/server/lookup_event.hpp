#pragma once

#include <chrono>

#include "dns/server/event.hpp"
#include "dns/server/event_type.hpp"
#include "experimental/expected.hpp"
#include "util/error.hpp"

namespace Dometer::Dns {
    class Packet;
}

namespace Dns = Dometer::Dns;
namespace Util = Dometer::Util;
using namespace std::experimental;

namespace Dometer::Dns::Server {
    class LookupEvent : public Event {
        public:
            LookupEvent(
                    const Dns::Packet& query,
                    const expected<Dns::Packet, Util::Error>& reply,
                    const std::chrono::duration<float, std::micro> duration);
            const std::chrono::duration<float, std::micro> getDuration() const;
            const Dns::Packet& getQuery() const;
            const expected<Dns::Packet, Util::Error>& getReply() const;
            EventType getType() const;
        private:
            const Dns::Packet& query;
            const expected<Dns::Packet, Util::Error>& reply;
            const std::chrono::duration<float, std::micro> duration;
    };
}
