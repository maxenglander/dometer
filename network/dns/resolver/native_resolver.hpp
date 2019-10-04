#pragma once

#include "experimental/expected.hpp"
#include "network/dns/packet.hpp"
#include "network/dns/resolver/resolution_mode.hpp"
#include "util/error.hpp"

using namespace Dometer::Network::Dns;
using namespace Dometer::Util;
using namespace std::experimental;

namespace Dometer::Network::Dns::Resolver {
    class NativeResolver {
        public:
            NativeResolver();
            NativeResolver(ResolutionMode);
            expected<Packet, Error> resolve(const Packet&) const;
        private:
            const ResolutionMode resolutionMode;
    };
}
