#pragma once

#include <string>

#include "powerdns/lookup_remote_backend_query.h"

namespace DnsTelemeter::PowerDns {
    class LookupRemoteBackendReply: public LookupRemoteBackendQuery {
        public:
            LookupRemoteBackendReply(std::string name, std::string type, std::string content, unsigned int ttl);
            const std::string content;
            const int ttl;
    };
}
