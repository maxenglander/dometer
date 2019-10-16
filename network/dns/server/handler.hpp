#pragma once

#include <memory>

#include "experimental/expected.hpp"
#include "network/dns/packet.hpp"
#include "network/dns/server/event.hpp"
#include "network/dns/server/event_type.hpp"
#include "util/callback.hpp"
#include "util/error.hpp"

using namespace Dometer::Network::Dns;
using namespace Dometer::Util;
using namespace std::experimental;

namespace Dometer::Network::Dns::Server {
    class Handler {
        public:
            virtual expected<size_t, Error> handle(
                    uint8_t *queryPtr, size_t querySize,
                    uint8_t *replyPtr, size_t replySize) = 0;
            virtual void on(EventType, Callback<Event&>) = 0;
    };
}
