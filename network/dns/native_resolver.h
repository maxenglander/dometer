#pragma once

#include <string>
#include <vector>

#include "network/dns/response.h"
#include "std/experimental/expected.h"
#include "util/error.h"

using namespace DnsTelemeter::Util;
using namespace std::experimental;

namespace DnsTelemeter::Network::Dns {
    class NativeResolver {
        public:
            expected<Response, Error> lookupA(std::string name);
    };
}
