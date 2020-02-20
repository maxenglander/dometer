#pragma once

#include <chrono>
#include <memory>

#include "dometer/dns/event/event_type.hpp"
#include "dometer/dns/handler/handler.hpp"
#include "dometer/dns/resolver/resolver.hpp"
#include "dometer/util/callback.hpp"
#include "dometer/util/callback_registry.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace dometer::dns {
    class Packet;
}

namespace dns = dometer::dns;
namespace util = dometer::util;

namespace dometer::dns::handler {
    class ResolvingHandler : public Handler {
        public:
            ResolvingHandler(
                    std::shared_ptr<dns::resolver::Resolver>);
            ResolvingHandler(
                    std::chrono::steady_clock,
                    util::CallbackRegistry<dns::event::EventType, std::shared_ptr<dns::event::Event>>,
                    std::shared_ptr<dns::resolver::Resolver>);
            std::x::expected<size_t, util::Error> handle(
                    uint8_t *queryPtr, size_t querySize,
                    uint8_t *replyPtr, size_t replySize);
            Handler& on(dns::event::EventType, util::Callback<std::shared_ptr<dns::event::Event>>);
        private:
            std::x::expected<dns::Packet, util::Error> handle(std::x::expected<dns::Packet, util::Error>& query);
            void notify(std::shared_ptr<dns::event::Event>);
            const std::chrono::steady_clock clock;
            util::CallbackRegistry<dns::event::EventType, std::shared_ptr<dns::event::Event>> listeners;
            const std::shared_ptr<dns::resolver::Resolver> resolver;
    };
}
