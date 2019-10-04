#pragma once

#include "experimental/expected.hpp"
#include "network/dns/packet.hpp"

using namespace Dometer::Network::Dns;
using namespace std::experimental;

namespace Dometer::Network::Dns {
    class Handler {
        public:
            virtual expected<Packet, Error> handle(Packet&) const = 0;
    };
}
