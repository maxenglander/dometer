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

namespace dns = dometer::dns;
namespace util = dometer::util;

namespace dometer::dns::resolver {
    class libresolv_resolver : public resolver {
        public:
            libresolv_resolver();
            libresolv_resolver(libresolv_function);
            std::x::expected<std::vector<uint8_t>, error> resolve(const std::string&, const class_&, const type&) const;
        private:
            const libresolv_function function;
    };
}
