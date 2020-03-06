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
    class resolving_handler : public Handler {
        public:
            resolving_handler(
                    dometer::event::emitter<dometer::dns::event::any_event>,
                    std::shared_ptr<dns::resolver::Resolver>);
            resolving_handler(std::chrono::steady_clock,
                    dometer::event::emitter<dometer::dns::event::any_event>,
                    std::shared_ptr<dns::resolver::Resolver>);
            std::x::expected<std::vector<uint8_t>, util::error> handle(uint64_t, std::vector<uint8_t>);
        private:
            std::x::expected<dns::message::message, util::error> handle(
                uint64_t, std::x::expected<dns::message::message, util::error>& query
            );
            std::x::expected<dns::message::message, util::error> handle(
                uint64_t, dns::message::message& query
            );
            std::x::expected<dns::message::message, util::error> handle(
                uint64_t, dometer::dns::question question
            );
            std::x::expected<dometer::dns::message::message, util::error> parseQuery(
                uint64_t sessionId, std::vector<uint8_t> bytes
            );
            std::x::expected<dometer::dns::message::message, util::error> parseReply(
                uint64_t sessionId, std::vector<uint8_t> bytes
            );
            std::x::expected<std::vector<uint8_t>, util::error> resolveQuery(
                uint64_t sessionId, dometer::dns::question&
            );

            const std::chrono::steady_clock clock;
            dometer::event::emitter<dometer::dns::event::any_event> emitter;
            const std::shared_ptr<dns::resolver::Resolver> resolver;
    };
}
