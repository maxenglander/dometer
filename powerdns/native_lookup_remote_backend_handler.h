#pragma once

#include <vector>

#include "network/dns/native_resolver.h"
#include "powerdns/lookup_remote_backend_handler.h"
#include "powerdns/lookup_remote_backend_query.h"
#include "powerdns/lookup_remote_backend_reply.h"

using namespace Dometer::Network;

namespace Dometer::PowerDns {
    class NativeLookupRemoteBackendHandler: public LookupRemoteBackendHandler {
        public:
            NativeLookupRemoteBackendHandler(Dns::NativeResolver resolver);
            std::vector<LookupRemoteBackendReply> handle(LookupRemoteBackendQuery query) override;
        private:
            Network::Dns::NativeResolver resolver;
    };
}
