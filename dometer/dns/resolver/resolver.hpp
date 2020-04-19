#pragma once

#include <vector>

#include "dometer/dns/message/message.hpp"
#include "dometer/dns/record/class.hpp"
#include "dometer/dns/record/type.hpp"
#include "dometer/dns/resolver/error.hpp"
#include "std/x/expected.hpp"

namespace dns = dometer::dns;

namespace dometer::dns::resolver {
    class resolver {
        public:
            virtual std::x::expected<std::vector<uint8_t>, error> resolve(
                const std::string&, const dometer::dns::record::class_&, const dometer::dns::record::type&
            ) const = 0;
    };
}
