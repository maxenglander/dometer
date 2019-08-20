#pragma once

#include <string>

namespace DnsTelemeter::PowerDns {
    class LookupQuery {
        public:
            LookupQuery(std::string qname, std::string qtype);
            LookupQuery(const LookupQuery&);
        private:
            const std::string qname;
            const std::string qtype;
    };
}
