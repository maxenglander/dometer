#include <string>

#include "powerdns/lookup_remote_backend_query.h"
#include "powerdns/lookup_remote_backend_reply.h"

namespace DnsTelemeter::PowerDns {
    LookupRemoteBackendReply::LookupRemoteBackendReply(LookupRemoteBackendQuery query, std::string content, unsigned int ttl)
        : LookupRemoteBackendQuery::LookupRemoteBackendQuery(query), content(content), ttl(ttl) {}
}
