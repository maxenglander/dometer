#pragma once

#include <vector>

#include "dometer/dns/message/message.hpp"
#include "dometer/dns/resolver/error.hpp"
#include "std/x/expected.hpp"

namespace dns = dometer::dns;

namespace dometer::dns::resolver {
    class Resolver {
        public:
            virtual std::x::expected<std::vector<uint8_t>, Error> resolve(
                const std::string&, const Class&, const Type&
            ) const = 0;
    };
}
