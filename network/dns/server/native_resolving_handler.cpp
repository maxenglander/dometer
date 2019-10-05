#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "experimental/expected.hpp"
#include "network/dns/resolver/native_resolver.hpp"
#include "network/dns/server/native_resolving_handler.hpp"
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
                CallbackRegistry<EventType, Event>(),
                NativeResolver())
    {}

    NativeResolvingHandler::NativeResolvingHandler(
                CallbackRegistry<EventType, Event> listeners,
                NativeResolver resolver)
        :   listeners(listeners),
            resolver(resolver)
    {}

    expected<size_t, Error> NativeResolvingHandler::handle(
            uint8_t *queryPtr, size_t querySize,
            uint8_t *replyPtr, size_t replySize) const {
        const auto query = Packet::makePacket(queryPtr, querySize);
        const auto reply = handle(query);

        if(reply) {
            uint8_t *replyPtrIn = *reply;
            std::copy(replyPtrIn, *reply + reply->size, replyPtr);
            return reply->size;
        } else {
            return unexpected<Error>(reply.error());
        }
    }

    expected<Packet, Error> NativeResolvingHandler::handle(const expected<Packet, Error> &query) const {
        if(!query) {
            return unexpected<Error>(query.error());
        }

        if(query->opcode() != Dns::Opcode::QUERY) {
            return Packet::notImplemented(*query);
        }

        if(query->qdcount() != 1) {
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

        return reply;
    }

    void NativeResolvingHandler::on(EventType eventType, std::shared_ptr<Callback<Event>> listener) {
        listeners.insert(eventType, listener);
    }
}
