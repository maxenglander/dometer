#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "dometer/dns/message/message.hpp"
#include "dometer/dns/message/message_factory.hpp"
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

    std::x::expected<size_t, util::Error> ResolvingHandler::handle(
            uint8_t *queryPtr, size_t querySize,
            uint8_t *replyPtr, size_t replySize) {
        auto query = dns::message::MessageFactory::makeMessage(queryPtr, querySize);
        notify(std::make_shared<dns::event::QueryEvent>(query));

        auto reply = handle(query);
        notify(std::make_shared<dns::event::ReplyEvent>(query, reply));

        if(reply) {
            uint8_t *replyPtrIn = *reply;
            std::copy(replyPtrIn, *reply + reply->size(), replyPtr);
            return reply->size();
        } else {
            return std::x::unexpected<util::Error>(util::Error(
                "Failed to obtain a reply for the query.",
                reply.error()
            ));
        }
    }

    std::x::expected<dns::message::Message, util::Error> ResolvingHandler::handle(std::x::expected<dns::message::Message, util::Error> &query) {
        if(!query) {
            auto error = util::Error(
                "The query is not valid.",
                query.error()
            );
            auto encoder = dometer::util::HumanErrorEncoder();
            std::cerr << encoder.encode(error) << std::endl;
            return std::x::unexpected<util::Error>(error);
        } else if(query->getOpCode() != dns::OpCode::QUERY) {
            return dns::message::MessageFactory::notImplemented(*query);
        }

        auto question = query->getQuestion();
        if(!question) {
            return dns::message::MessageFactory::formatError(*query);
        }

        auto start = clock.now();
        auto reply = resolver->resolve(question->qname, question->qclass, question->qtype);
        auto end = clock.now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        if(reply) reply->setId(query->getId());

        notify(std::make_shared<dns::event::LookupEvent>(*query, reply, duration));

        return reply;
    }

    void ResolvingHandler::notify(std::shared_ptr<dns::event::Event> event) {
        listeners.notify(event->getType(), event);
    }

    Handler& ResolvingHandler::on(dns::event::EventType eventType, util::Callback<std::shared_ptr<dns::event::Event>> listener) {
        listeners.on(eventType, listener);
        return *this;
    }
}
