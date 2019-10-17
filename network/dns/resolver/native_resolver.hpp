#pragma once

#include <string>

#include "experimental/expected.hpp"
#include "network/dns/class.hpp"
#include "network/dns/type.hpp"
#include "network/dns/resolver/resolution_mode.hpp"
#include "util/error.hpp"

namespace Dometer::Network::Dns {
    class Packet;
}

namespace Dns = Dometer::Network::Dns;
namespace Util = Dometer::Util;
using namespace std::experimental;

namespace Dometer::Network::Dns::Resolver {
    class NativeResolver {
        public:
            NativeResolver();
            NativeResolver(ResolutionMode);
            expected<Dns::Packet, Util::Error> resolve(const std::string&, const Class&, const Type&) const;
        private:
            const ResolutionMode resolutionMode;
    };
}
