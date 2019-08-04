#pragma once

#include <string>

namespace DnsTelemeter {
    namespace Dns {
        class Resolver {
            public:
                std::vector<DnsTelemeter::Dns::Answer> lookup(DnsTelemeter::Dns::Query query);
        };
    }
}
