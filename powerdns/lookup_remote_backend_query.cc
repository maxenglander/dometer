#include <string>

#include "powerdns/lookup_remote_backend_query.h"

namespace DnsTelemeter::PowerDns {
    LookupRemoteBackendQuery::LookupRemoteBackendQuery(std::string qname, std::string qtype) 
        : qname(qname), qtype(qtype) {}
    LookupRemoteBackendQuery::LookupRemoteBackendQuery(const LookupRemoteBackendQuery& query)
        : LookupRemoteBackendQuery(query.qname, query.qtype) {}
}
