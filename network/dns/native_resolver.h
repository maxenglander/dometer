#pragma once

#include <string>
#include <vector>

#include "network/dns/answer.h"
#include "std/experimental/expected.h"

using namespace std::experimental;

namespace DnsTelemeter::Network::Dns {
    class NativeResolver {
        public:
            expected<std::vector<Answer>, int> lookupA(std::string name);
    };
}
