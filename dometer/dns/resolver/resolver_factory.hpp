#pragma once

#include <memory>

#include "dometer/dns/resolver/libresolv_options.hpp"
#include "dometer/dns/resolver/options.hpp"
#include "std/x/expected.hpp"

namespace dometer::dns::resolver {
    class resolver_factory {
        public:
            static std::x::expected<std::shared_ptr<resolver>, util::error> make_resolver(libresolv_options);
            static std::x::expected<std::shared_ptr<resolver>, util::error> make_resolver(options);
    };
}
