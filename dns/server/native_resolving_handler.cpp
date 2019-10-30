#include <chrono>
#include <iostream>
#include <memory>

#include "dns/packet.hpp"
#include "dns/resolver/native_resolver.hpp"
#include "dns/server/event.hpp"
#include "dns/server/event_type.hpp"
#include "dns/server/lookup_event.hpp"
#include "dns/server/native_resolving_handler.hpp"
#include "dns/server/query_event.hpp"
#include "dns/server/reply_event.hpp"
#include "experimental/expected.hpp"
#include "util/callback.hpp"
#include "util/callback_registry.hpp"
#include "util/error.hpp"

using namespace Dometer::Dns;
using namespace Dometer::Dns::Resolver;
using namespace Dometer::Util;
using namespace std::experimental;

namespace Dometer::Dns::Server {
    NativeResolvingHandler::NativeResolvingHandler()
        :   NativeResolvingHandler(
                std::chrono::steady_clock(),
                CallbackRegistry<EventType, std::shared_ptr<Event>>(),
                NativeResolver())
    {}

    NativeResolvingHandler::NativeResolvingHandler(
                std::chrono::steady_clock clock,
                CallbackRegistry<EventType, std::shared_ptr<Event>> listeners,
                NativeResolver resolver)
        :   clock(clock),
            listeners(listeners),
            resolver(resolver)
    {}

    expected<size_t, Error> NativeResolvingHandler::handle(
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

    expected<Packet, Error> NativeResolvingHandler::handle(expected<Packet, Error> &query) {
        if(!query) {
            return unexpected<Error>(query.error());
        } else if(query->getOpCode() != Dns::OpCode::QUERY) {
            return Packet::notImplemented(*query);
        }

        auto question = query->getQuestion();
        if(!question) {
            return Packet::formatError(*query);
        }

        auto start = clock.now();
        auto reply = resolver.resolve(question->qname, question->qclass, question->qtype);
        auto end = clock.now();

        if(reply) {
            std::cout << "updating reply id" << std::endl;
            reply->setId(query->getId());
        } else {
            std::cout << "got a bad reply" << std::endl;
        }

        notify(std::make_shared<LookupEvent>(*query, reply,
                    std::chrono::duration_cast<std::chrono::microseconds>(end - start)));

        return reply;
    }

    void NativeResolvingHandler::notify(std::shared_ptr<Event> event) {
        listeners.notify(event->getType(), event);
    }

    Handler& NativeResolvingHandler::on(EventType eventType, Callback<std::shared_ptr<Event>> listener) {
        listeners.on(eventType, listener);
        return *this;
    }
}
