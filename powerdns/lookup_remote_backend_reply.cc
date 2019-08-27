#include <string>

#include "powerdns/lookup_remote_backend_query.h"
#include "powerdns/lookup_remote_backend_reply.h"

namespace DnsTelemeter::PowerDns {
    LookupRemoteBackendReply::LookupRemoteBackendReply(std::string name, std::string type, std::string content, unsigned int ttl)
        : LookupRemoteBackendQuery::LookupRemoteBackendQuery(name, type), content(content), ttl(ttl) {}
}
