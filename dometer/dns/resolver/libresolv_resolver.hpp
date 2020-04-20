#pragma once

#include <resolv.h>
#include <string>
#include <vector>

#include "dometer/dns/record/class.hpp"
#include "dometer/dns/record/type.hpp"
#include "dometer/dns/resolver/error.hpp"
#include "dometer/dns/resolver/libresolv_function.hpp"
#include "dometer/dns/resolver/resolver.hpp"
#include "std/x/expected.hpp"

namespace dns = dometer::dns;

namespace dometer::dns::resolver {
    class libresolv_resolver : public resolver {
        public:
            libresolv_resolver(struct __res_state);
            libresolv_resolver(libresolv_function, struct __res_state);
            ~libresolv_resolver();
            std::x::expected<std::vector<uint8_t>, error> resolve(const std::string&,
                                                                  const dometer::dns::record::class_&,
                                                                  const dometer::dns::record::type&) const;
        private:
            const libresolv_function function;
            struct __res_state stat;
    };
}
