#include "experimental/expected.hpp"
#include "network/dns/resolver/native_resolver.hpp"
#include "network/dns/server/native_resolving_handler.hpp"
#include "util/error.hpp"

using namespace Dometer::Util;
using namespace Dometer::Network::Dns;
using namespace Dometer::Network::Dns::Resolver;
using namespace std::experimental;

namespace Dometer::Network::Dns::Server {
    NativeResolvingHandler::NativeResolvingHandler() : NativeResolvingHandler(NativeResolver()) {}
    NativeResolvingHandler::NativeResolvingHandler(NativeResolver resolver) : resolver(resolver) {}

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
        } else if(query->opcode() != Dns::Opcode::QUERY) {
            return Packet::notImplemented(*query);
        } else if(query->qdcount() != 1) {
            return Packet::formatError(*query);
        } else {
            auto question = query->question();
            if(!question) {
                return Packet::formatError(*query);
            } else {
                return resolver.resolve(*query);
            }
        }
    }
}
