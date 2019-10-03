#include "experimental/expected.hpp"
#include "network/dns/native_resolver.hpp"
#include "network/dns/native_resolving_handler.hpp"
#include "util/error.hpp"

using namespace Dometer::Util;
using namespace std::experimental;

namespace Dometer::Network::Dns {
    NativeResolvingHandler::NativeResolvingHandler() : NativeResolvingHandler(NativeResolver()) {}
    NativeResolvingHandler::NativeResolvingHandler(NativeResolver resolver) : resolver(resolver) {}

    expected<Packet, Error> NativeResolvingHandler::handle(Packet& query) const {
        if(query.opcode() != Dns::Opcode::QUERY)
            return Packet::notImplemented(query);

        if(query.qdcount() != 1)
            return Packet::formatError(query);

        auto question = query.question();
        
        if(!question)
            return Packet::formatError(query);

        return resolver.resolve(query);
    }
}
