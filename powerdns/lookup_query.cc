#include <string>

#include "powerdns/lookup_query.h"

namespace DnsTelemeter::PowerDns {
    LookupQuery::LookupQuery(std::string qname, std::string qtype) 
        : qname(qname), qtype(qtype) {}
    LookupQuery::LookupQuery(const LookupQuery& query)
        : LookupQuery(query.qname, query.qtype) {}
}
