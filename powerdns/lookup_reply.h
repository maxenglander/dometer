#pragma once

#include <string>

#include "powerdns/lookup_query.h"

namespace DnsTelemeter::PowerDns {
    class LookupReply: public LookupQuery {
        public:
            LookupReply(LookupQuery, std::string content, unsigned int ttl);
            const std::string content;
            const int ttl;
    };
}
