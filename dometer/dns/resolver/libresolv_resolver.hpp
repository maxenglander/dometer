#pragma once

#include <string>
#include <vector>

#include "dometer/dns/class.hpp"
#include "dometer/dns/type.hpp"
#include "dometer/dns/resolver/error.hpp"
#include "dometer/dns/resolver/libresolv_function.hpp"
#include "dometer/dns/resolver/resolver.hpp"
#include "std/x/expected.hpp"
#include "dometer/util/error.hpp"

namespace dometer::dns {
    class Packet;
}

namespace dns = dometer::dns;
namespace util = dometer::util;

namespace dometer::dns::resolver {
    class LibresolvResolver : public Resolver {
        public:
            LibresolvResolver();
            LibresolvResolver(LibresolvFunction);
            std::x::expected<std::vector<uint8_t>, error> resolve(const std::string&, const Class&, const Type&) const;
        private:
            const LibresolvFunction function;
    };
}
