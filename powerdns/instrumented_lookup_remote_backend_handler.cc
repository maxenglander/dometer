#include <memory>
#include <vector>

#include "powerdns/lookup_remote_backend_query.h"
#include "powerdns/lookup_remote_backend_reply.h"
#include "powerdns/instrumented_lookup_remote_backend_handler.h"

namespace DnsTelemeter::PowerDns {
    InstrumentedLookupRemoteBackendHandler::InstrumentedLookupRemoteBackendHandler(std::shared_ptr<LookupRemoteBackendHandler> realHandler)
    : realHandler(realHandler) {}

    std::vector<LookupRemoteBackendReply> InstrumentedLookupRemoteBackendHandler::handle(LookupRemoteBackendQuery query) {
        return realHandler->handle(query);
    }
}
