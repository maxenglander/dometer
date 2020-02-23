#pragma once

#include <string>

#include "dometer/dns/class.hpp"
#include "dometer/dns/type.hpp"
#include "dometer/dns/resolver/libresolv_function.hpp"
#include "dometer/dns/resolver/resolver.hpp"
#include "std/x/expected.hpp"
#include "dometer/util/error.hpp"

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
            expected<dns::message::Message, util::Error> resolve(const std::string&, const Class&, const Type&) const;
        private:
            const LibresolvFunction function;
    };
}
