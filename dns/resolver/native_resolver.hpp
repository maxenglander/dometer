#pragma once

#include <string>

#include "dns/class.hpp"
#include "dns/type.hpp"
#include "dns/resolver/resolution_mode.hpp"
#include "x/expected.hpp"
#include "util/error.hpp"

namespace dometer::dns {
    class Packet;
}

namespace Dns = dometer::dns;
namespace util = dometer::util;
using namespace std::x;

namespace dometer::dns::resolver {
    class NativeResolver {
        public:
            NativeResolver();
            NativeResolver(ResolutionMode);
            expected<dns::Packet, util::Error> resolve(const std::string&, const Class&, const Type&) const;
        private:
            const ResolutionMode resolutionMode;
    };
}
