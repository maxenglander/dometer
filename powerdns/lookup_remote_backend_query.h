#pragma once

#include <string>

namespace DnsTelemeter::PowerDns {
    class LookupRemoteBackendQuery {
        public:
            LookupRemoteBackendQuery(std::string qname, std::string qtype);
            LookupRemoteBackendQuery(const LookupRemoteBackendQuery&);
            const std::string qname;
            const std::string qtype;
    };
}
