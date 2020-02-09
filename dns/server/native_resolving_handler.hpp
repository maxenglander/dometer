#pragma once

#include <chrono>
#include <memory>

#include "dns/resolver/native_resolver.hpp"
#include "dns/server/event_type.hpp"
#include "dns/server/handler.hpp"
#include "x/expected.hpp"
#include "util/callback.hpp"
#include "util/callback_registry.hpp"
#include "util/error.hpp"

namespace dometer::dns {
    class Packet;
}

namespace Dns = dometer::dns;
namespace util = dometer::util;
using namespace std::x;

namespace dometer::dns::server {
    class NativeResolvingHandler : public Handler {
        public:
            NativeResolvingHandler();
            NativeResolvingHandler(
                    std::chrono::steady_clock,
                    util::CallbackRegistry<EventType, std::shared_ptr<Event>>,
                    dns::resolver::NativeResolver);
            expected<size_t, util::Error> handle(
                    uint8_t *queryPtr, size_t querySize,
                    uint8_t *replyPtr, size_t replySize);
            Handler& on(EventType, util::Callback<std::shared_ptr<Event>>);
        private:
            expected<dns::Packet, util::Error> handle(expected<dns::Packet, util::Error>& query);
            void notify(std::shared_ptr<Event>);
            const std::chrono::steady_clock clock;
            util::CallbackRegistry<EventType, std::shared_ptr<Event>> listeners;
            const dns::resolver::NativeResolver resolver;
    };
}
