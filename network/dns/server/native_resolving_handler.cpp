#include <chrono>
#include <memory>

#include "experimental/expected.hpp"
#include "network/dns/packet.hpp"
#include "network/dns/resolver/native_resolver.hpp"
#include "network/dns/server/event.hpp"
#include "network/dns/server/event_type.hpp"
#include "network/dns/server/lookup_event.hpp"
#include "network/dns/server/native_resolving_handler.hpp"
#include "network/dns/server/query_event.hpp"
#include "network/dns/server/reply_event.hpp"
#include "util/callback.hpp"
#include "util/callback_registry.hpp"
#include "util/error.hpp"

using namespace Dometer::Util;
using namespace Dometer::Network::Dns;
using namespace Dometer::Network::Dns::Resolver;
using namespace std::experimental;

namespace Dometer::Network::Dns::Server {
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
        } else if(query->opcode() != Dns::Opcode::QUERY) {
            return Packet::notImplemented(*query);
        } else if(query->qdcount() != 1) {
            return Packet::formatError(*query);
        }

        auto question = query->question();
        if(!question) {
            return Packet::formatError(*query);
        }

        auto reply = resolver.resolve(question->qname, question->qclass, question->qtype);
        if(reply) {
            reply->setId(query->id());
        }

        notify(std::make_shared<LookupEvent>(*query, reply));

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
