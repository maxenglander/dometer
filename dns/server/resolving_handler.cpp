#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "dns/packet.hpp"
#include "dns/resolver/resolver.hpp"
#include "dns/server/event.hpp"
#include "dns/server/event_type.hpp"
#include "dns/server/lookup_event.hpp"
#include "dns/server/query_event.hpp"
#include "dns/server/reply_event.hpp"
#include "dns/server/resolving_handler.hpp"
#include "x/expected.hpp"
#include "util/callback.hpp"
#include "util/callback_registry.hpp"
#include "util/error.hpp"

using namespace dometer::dns;
using namespace dometer::dns::resolver;
using namespace dometer::util;
using namespace std::x;

namespace dometer::dns::server {
    ResolvingHandler::ResolvingHandler(std::shared_ptr<dns::resolver::Resolver> resolver)
        :   ResolvingHandler(
                std::chrono::steady_clock(),
                CallbackRegistry<EventType, std::shared_ptr<Event>>(),
                resolver)
    {}

    ResolvingHandler::ResolvingHandler(
                std::chrono::steady_clock clock,
                CallbackRegistry<EventType, std::shared_ptr<Event>> listeners,
                std::shared_ptr<dns::resolver::Resolver> resolver)
        :   clock(clock),
            listeners(listeners),
            resolver(resolver)
    {}

    expected<size_t, Error> ResolvingHandler::handle(
            uint8_t *queryPtr, size_t querySize,
            uint8_t *replyPtr, size_t replySize) {
        auto query = Packet::makePacket(queryPtr, querySize);
        notify(std::make_shared<QueryEvent>(query));

        auto reply = handle(query);
        notify(std::make_shared<ReplyEvent>(query, reply));

        if(reply) {
            uint8_t *replyPtrIn = *reply;
            std::copy(replyPtrIn, *reply + reply->size, replyPtr);
            return reply->size;
        } else {
            return unexpected<Error>(reply.error());
        }
    }

    expected<Packet, Error> ResolvingHandler::handle(expected<Packet, Error> &query) {
        if(!query) {
            return unexpected<Error>(query.error());
        } else if(query->getOpCode() != dns::OpCode::QUERY) {
            return Packet::notImplemented(*query);
        }

        auto question = query->getQuestion();
        if(!question) {
            return Packet::formatError(*query);
        }

        auto start = clock.now();
        auto reply = resolver->resolve(question->qname, question->qclass, question->qtype);
        auto end = clock.now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        if(reply) reply->setId(query->getId());

        notify(std::make_shared<LookupEvent>(*query, reply, duration));

        return reply;
    }

    void ResolvingHandler::notify(std::shared_ptr<Event> event) {
        listeners.notify(event->getType(), event);
    }

    Handler& ResolvingHandler::on(EventType eventType, Callback<std::shared_ptr<Event>> listener) {
        listeners.on(eventType, listener);
        return *this;
    }
}
