#pragma once

#include <chrono>
#include <memory>

#include "dns/resolver/native_resolver.hpp"
#include "dns/server/event_type.hpp"
#include "dns/server/handler.hpp"
#include "experimental/expected.hpp"
#include "util/callback.hpp"
#include "util/callback_registry.hpp"
#include "util/error.hpp"

namespace Dometer::Dns {
    class Packet;
}

namespace Dns = Dometer::Dns;
namespace Util = Dometer::Util;
using namespace std::experimental;

namespace Dometer::Dns::Server {
    class NativeResolvingHandler : public Handler {
        public:
            NativeResolvingHandler();
            NativeResolvingHandler(
                    std::chrono::steady_clock,
                    Util::CallbackRegistry<EventType, std::shared_ptr<Event>>,
                    Dns::Resolver::NativeResolver);
            expected<size_t, Util::Error> handle(
                    uint8_t *queryPtr, size_t querySize,
                    uint8_t *replyPtr, size_t replySize);
            Handler& on(EventType, Util::Callback<std::shared_ptr<Event>>);
        private:
            expected<Dns::Packet, Util::Error> handle(expected<Dns::Packet, Util::Error>& query);
            void notify(std::shared_ptr<Event>);
            const std::chrono::steady_clock clock;
            Util::CallbackRegistry<EventType, std::shared_ptr<Event>> listeners;
            const Dns::Resolver::NativeResolver resolver;
    };
}
