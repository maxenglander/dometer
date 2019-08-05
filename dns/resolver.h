#pragma once

#include <string>

#include "dns/query.h"
#include "dns/result.h"

namespace DnsTelemeter {
    namespace Dns {
        class Resolver {
            public:
                Result lookupA(std::string name);
        };
    }
}
