#pragma once

#include <memory>
#include <vector>

#include "powerdns/lookup_remote_backend_handler.h"
#include "powerdns/lookup_remote_backend_query.h"
#include "powerdns/lookup_remote_backend_reply.h"

namespace DnsTelemeter::PowerDns {
    class InstrumentedLookupRemoteBackendHandler: public LookupRemoteBackendHandler {
        public:
            InstrumentedLookupRemoteBackendHandler(std::shared_ptr<LookupRemoteBackendHandler> realHandler);
        protected:
            std::vector<LookupRemoteBackendReply> handle(LookupRemoteBackendQuery query) override;
        private:
            std::shared_ptr<LookupRemoteBackendHandler> realHandler;
    };
}
