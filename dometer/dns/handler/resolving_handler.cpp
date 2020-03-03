#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "dometer/dns/message/message.hpp"
#include "dometer/dns/message/factory.hpp"
#include "dometer/dns/message/parser.hpp"
#include "dometer/dns/resolver/resolver.hpp"
#include "dometer/dns/event/event.hpp"
#include "dometer/dns/event/event_type.hpp"
#include "dometer/dns/event/lookup_event.hpp"
#include "dometer/dns/event/query_event.hpp"
#include "dometer/dns/event/reply_event.hpp"
#include "dometer/dns/handler/resolving_handler.hpp"
#include "dometer/util/callback.hpp"
#include "dometer/util/callback_registry.hpp"
#include "dometer/util/error.hpp"
#include "dometer/util/human_error_encoder.hpp"
#include "std/x/expected.hpp"

namespace dns = dometer::dns;
namespace util = dometer::util;

namespace dometer::dns::handler {
    ResolvingHandler::ResolvingHandler(std::shared_ptr<dns::resolver::Resolver> resolver)
        :   ResolvingHandler(
                std::chrono::steady_clock(),
                util::CallbackRegistry<dns::event::EventType, std::shared_ptr<dns::event::Event>>(),
                resolver)
    {}

    ResolvingHandler::ResolvingHandler(
                std::chrono::steady_clock clock,
                util::CallbackRegistry<dns::event::EventType, std::shared_ptr<dns::event::Event>> listeners,
                std::shared_ptr<dns::resolver::Resolver> resolver)
        :   clock(clock),
            listeners(listeners),
            resolver(resolver)
    {}

    std::x::expected<std::vector<uint8_t>, util::Error> ResolvingHandler::handle(
        uint64_t sessionId, std::vector<uint8_t> queryBytes
    ) {
        auto query = dns::message::Parser::parse(queryBytes);
        auto reply = handle(sessionId, query);

        if(!reply) {
            return std::x::unexpected<util::Error>(reply.error());
        }

        const uint8_t* replyPtr = *reply;
        return std::vector<uint8_t>(replyPtr, replyPtr + reply->size());
    }

    std::x::expected<dns::message::Message, util::Error> ResolvingHandler::handle(
        uint64_t sessionId,
        std::x::expected<dns::message::Message, util::Error> &query
    ) {
        if(!query) {
            return std::x::unexpected<util::Error>(util::Error("The query is not valid.", query.error()));
        }

        if(query->getOpCode() != dns::OpCode::QUERY) {
            return dns::message::Factory::notImplemented(*query);
        }

        auto question = query->getQuestion();
        if(!question) {
            return dns::message::Factory::formatError(*query);
        }

        auto start = clock.now();
        auto resolution = resolver->resolve(question->qname, question->qclass, question->qtype);
        auto end = clock.now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        if(!resolution) {
            return std::x::unexpected<dometer::util::Error>(static_cast<dometer::util::Error>(resolution.error()));
        }

        auto reply = dometer::dns::message::Parser::parse(*resolution);

        if(reply) {
            reply->setId(query->getId());
            return *reply;
        } else {
            return std::x::unexpected<dometer::util::Error>(reply.error());
        }
    }

    void ResolvingHandler::notify(std::shared_ptr<dns::event::Event> event) {
        listeners.notify(event->getType(), event);
    }

    Handler& ResolvingHandler::on(dns::event::EventType eventType, util::Callback<std::shared_ptr<dns::event::Event>> listener) {
        listeners.on(eventType, listener);
        return *this;
    }
}
