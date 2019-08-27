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

        auto dnsResponse = resolver.lookup(query.qname, query.qtype);

        if(!dnsResponse) {
            std::cerr << dnsResponse.error().message + "\n";
            return result;
        } else {
            std::cerr << "Got some answers, rcode = " + std::to_string(dnsResponse->header.rcode) + "\n";
        }

        auto answers = dnsResponse->answers; 

        for(auto it = answers.begin(); it < answers.end(); it++) {
            result.push_back(LookupRemoteBackendReply(it->name, it->type, it->content, it->ttl));
        }

        return result;
    }
}
