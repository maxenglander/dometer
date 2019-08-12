#pragma once

#include <string>

#include "network/dns/result.h"
#include "std/experimental/expected.h"

using namespace std::experimental;

namespace DnsTelemeter::Network::Dns {
    class Resolver {
        public:
            expected<Result, int> lookupA(std::string name);
    };
}