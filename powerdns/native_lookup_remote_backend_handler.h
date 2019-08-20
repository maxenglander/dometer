#pragma once

#include "network/dns/resolver.h"
#include "powerdns/lookup_remote_backend_handler.h"

using namespace DnsTelemeter::Network;

namespace DnsTelemeter::PowerDns {
    class NativeLookupRemoteBackendHandler: public LookupRemoteBackendHandler {
        public:
            NativeLookupRemoteBackendHandler(Dns::Resolver resolver);
        protected:
            std::vector<LookupReply> handle(LookupQuery query);
        private:
            Network::Dns::Resolver resolver;
    };
}
