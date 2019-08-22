#include <vector>

#include "network/dns/native_resolver.h"
#include "powerdns/lookup_remote_backend_query.h"
#include "powerdns/lookup_remote_backend_reply.h"
#include "powerdns/native_lookup_remote_backend_handler.h"

using namespace DnsTelemeter::Network;

namespace DnsTelemeter::PowerDns {
    NativeLookupRemoteBackendHandler::NativeLookupRemoteBackendHandler(Dns::NativeResolver resolver) {
        this->resolver = resolver;
    }

    std::vector<LookupRemoteBackendReply> NativeLookupRemoteBackendHandler::handle(LookupRemoteBackendQuery query) {
        std::vector<LookupRemoteBackendReply> result;
        return result;
    }
}
