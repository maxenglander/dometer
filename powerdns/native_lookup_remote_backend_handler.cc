#include <vector>

#include "network/dns/resolver.h"
#include "powerdns/lookup_query.h"
#include "powerdns/lookup_reply.h"
#include "powerdns/native_lookup_remote_backend_handler.h"

using namespace DnsTelemeter::Network;

namespace DnsTelemeter::PowerDns {
    NativeLookupRemoteBackendHandler::NativeLookupRemoteBackendHandler(Dns::Resolver resolver) {
        this->resolver = resolver;
    }

    std::vector<LookupReply> NativeLookupRemoteBackendHandler::handle(LookupQuery query) {
        std::vector<LookupReply> result;
        return result;
    }
}
