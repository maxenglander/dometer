#pragma once

#include <string>

#include "dns/query.h"
#include "dns/result.h"

#include "std/experimental/expected.h"

using namespace std::experimental;

namespace DnsTelemeter {
    namespace Dns {
        class Resolver {
            public:
                expected<Result, int> lookupA(std::string name);
        };
    }
}
