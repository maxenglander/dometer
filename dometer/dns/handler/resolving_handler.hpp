#pragma once

#include <chrono>
#include <memory>
#include <vector>

#include "dometer/dns/event/any_event.hpp"
#include "dometer/dns/handler/handler.hpp"
#include "dometer/dns/resolver/resolver.hpp"
#include "dometer/event/callback.hpp"
#include "dometer/event/emitter.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::dns::handler {
    class ResolvingHandler : public Handler {
        public:
            ResolvingHandler(
                    dometer::event::Emitter<dometer::dns::event::AnyEvent>,
                    std::shared_ptr<dns::resolver::Resolver>);
            ResolvingHandler(std::chrono::steady_clock,
                    dometer::event::Emitter<dometer::dns::event::AnyEvent>,
                    std::shared_ptr<dns::resolver::Resolver>);
            std::x::expected<std::vector<uint8_t>, util::Error> handle(uint64_t, std::vector<uint8_t>);
        private:
            std::x::expected<dns::message::Message, util::Error> handle(
                uint64_t, std::x::expected<dns::message::Message, util::Error>& query
            );
            std::x::expected<dns::message::Message, util::Error> handle(
                uint64_t, dns::message::Message& query
            );
            std::x::expected<dns::message::Message, util::Error> handle(
                uint64_t, dometer::dns::Question question
            );
            std::x::expected<dometer::dns::message::Message, util::Error> parseQuery(
                uint64_t sessionId, std::vector<uint8_t> bytes
            );
            std::x::expected<dometer::dns::message::Message, util::Error> parseReply(
                uint64_t sessionId, std::vector<uint8_t> bytes
            );
            std::x::expected<std::vector<uint8_t>, util::Error> resolveQuery(
                uint64_t sessionId, dometer::dns::Question&
            );

            const std::chrono::steady_clock clock;
            dometer::event::Emitter<dometer::dns::event::AnyEvent> emitter;
            const std::shared_ptr<dns::resolver::Resolver> resolver;
    };
}
