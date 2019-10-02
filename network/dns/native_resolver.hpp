#pragma once

#include "experimental/expected.hpp"
#include "network/dns/packet.hpp"
#include "network/dns/resolution_mode.hpp"
#include "util/error.hpp"

using namespace Dometer::Util;
using namespace std::experimental;

namespace Dometer::Network::Dns {
    class NativeResolver {
        public:
            NativeResolver();
            NativeResolver(ResolutionMode);
            expected<Packet, Error> resolve(Packet&) const;
        private:
            const ResolutionMode resolutionMode;
    };
}
