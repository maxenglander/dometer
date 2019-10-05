#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "experimental/expected.hpp"
#include "network/dns/packet.hpp"
#include "network/dns/resolver/native_resolver.hpp"
#include "network/dns/server/event.hpp"
#include "network/dns/server/event_type.hpp"
#include "network/dns/server/handler.hpp"
#include "util/callback.hpp"
#include "util/callback_registry.hpp"
#include "util/error.hpp"

using namespace Dometer::Network::Dns;
using namespace Dometer::Network::Dns::Resolver;
using namespace Dometer::Util;
using namespace std::experimental;

namespace Dometer::Network::Dns::Server {
    class NativeResolvingHandler : public Handler {
        public:
            NativeResolvingHandler();
            NativeResolvingHandler(
                    CallbackRegistry<EventType, Event>,
                    NativeResolver);
            expected<size_t, Error> handle(
                    uint8_t *queryPtr, size_t querySize,
                    uint8_t *replyPtr, size_t replySize) const;
            void on(EventType, std::shared_ptr<Callback<Event>>);
        private:
            expected<Packet, Error> handle(const expected<Packet, Error> &query) const;
            void notify(EventType, Event) const;
            CallbackRegistry<EventType, Event> listeners;
            const NativeResolver resolver;
    };
}
