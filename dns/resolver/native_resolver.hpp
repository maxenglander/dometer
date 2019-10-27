#pragma once

#include <string>

#include "dns/class.hpp"
#include "dns/type.hpp"
#include "dns/resolver/resolution_mode.hpp"
#include "experimental/expected.hpp"
#include "util/error.hpp"

namespace Dometer::Dns {
    class Packet;
}

namespace Dns = Dometer::Dns;
namespace Util = Dometer::Util;
using namespace std::experimental;

namespace Dometer::Dns::Resolver {
    class NativeResolver {
        public:
            NativeResolver();
            NativeResolver(ResolutionMode);
            expected<Dns::Packet, Util::Error> resolve(const std::string&, const Class&, const Type&) const;
        private:
            const ResolutionMode resolutionMode;
    };
}
