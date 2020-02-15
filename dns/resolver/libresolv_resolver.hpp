#pragma once

#include <string>

#include "dns/class.hpp"
#include "dns/type.hpp"
#include "dns/resolver/libresolv_function.hpp"
#include "dns/resolver/resolver.hpp"
#include "x/expected.hpp"
#include "util/error.hpp"

namespace dometer::dns {
    class Packet;
}

namespace dns = dometer::dns;
namespace util = dometer::util;
using namespace std::x;

namespace dometer::dns::resolver {
    class LibresolvResolver : public Resolver {
        public:
            LibresolvResolver();
            LibresolvResolver(LibresolvFunction);
            expected<dns::Packet, util::Error> resolve(const std::string&, const Class&, const Type&) const;
        private:
            const LibresolvFunction function;
    };
}
