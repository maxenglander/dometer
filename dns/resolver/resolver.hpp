#pragma once

#include "dns/packet.hpp"
#include "util/error.hpp"
#include "x/expected.hpp"

namespace dns = dometer::dns;
namespace util = dometer::util;
using namespace std::x;

namespace dometer::dns::resolver {
    class Resolver {
        public:
            virtual expected<dns::Packet, util::Error> resolve(const std::string&, const Class&, const Type&) const = 0;
    };
}
