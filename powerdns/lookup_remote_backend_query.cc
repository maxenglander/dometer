#include <string>

#include "powerdns/lookup_remote_backend_query.h"

namespace Dometer::PowerDns {
    LookupRemoteBackendQuery::LookupRemoteBackendQuery(std::string qtype, std::string qname) 
        : qname(qname), qtype(qtype) {}
    LookupRemoteBackendQuery::LookupRemoteBackendQuery(const LookupRemoteBackendQuery& query)
        : LookupRemoteBackendQuery(query.qtype, query.qname) {}
}
