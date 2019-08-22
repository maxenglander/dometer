#pragma once

#include <string>

namespace DnsTelemeter::PowerDns {
    class LookupRemoteBackendQuery {
        public:
            LookupRemoteBackendQuery(std::string qname, std::string qtype);
            LookupRemoteBackendQuery(const LookupRemoteBackendQuery&);
        private:
            const std::string qname;
            const std::string qtype;
    };
}
