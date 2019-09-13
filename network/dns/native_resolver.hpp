#pragma once

#include "experimental/expected.hpp"
#include "network/dns/packet.hpp"
#include "util/error.hpp"

using namespace Dometer::Util;
using namespace std::experimental;

namespace Dometer::Network::Dns {
    class NativeResolver {
        public:
            expected<Packet, Error> resolve(Packet);
    };
}
