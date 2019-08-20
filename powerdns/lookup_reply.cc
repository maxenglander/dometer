#include <string>

#include "powerdns/lookup_query.h"
#include "powerdns/lookup_reply.h"

namespace DnsTelemeter::PowerDns {
    LookupReply::LookupReply(LookupQuery query, std::string content, unsigned int ttl)
        : LookupQuery::LookupQuery(query), content(content), ttl(ttl) {}
}
