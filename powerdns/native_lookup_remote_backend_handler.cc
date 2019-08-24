#include <iostream>
#include <vector>

#include "network/dns/native_resolver.h"
#include "powerdns/lookup_remote_backend_query.h"
#include "powerdns/lookup_remote_backend_reply.h"
#include "powerdns/remote_backend_replies.h"
#include "powerdns/native_lookup_remote_backend_handler.h"

using namespace DnsTelemeter::Network;

namespace DnsTelemeter::PowerDns {
    NativeLookupRemoteBackendHandler::NativeLookupRemoteBackendHandler(Dns::NativeResolver resolver)
    : resolver(resolver) {}

    std::vector<LookupRemoteBackendReply> NativeLookupRemoteBackendHandler::handle(LookupRemoteBackendQuery query) {
        std::vector<LookupRemoteBackendReply> result;

        if(query.qtype != "A") {
            return result;
        }

        auto dnsResponse = resolver.lookupA(query.qname);

        if(!dnsResponse) {
            return result;
        }

        auto answers = dnsResponse->answers; 

        for(auto it = answers.begin(); it < answers.end(); it++) {
            result.push_back(LookupRemoteBackendReply(query, it->content, it->ttl));
        }

        return result;
    }
}
