#pragma once

#include <memory>

#include "dometer/dns/resolver/libresolv_options.hpp"
#include "dometer/dns/resolver/options.hpp"

namespace dometer::dns::resolver {
    class resolver_factory {
        public:
            static std::shared_ptr<Resolver> make_resolver(libresolv_options);
            static std::shared_ptr<Resolver> make_resolver(options);
    };
}
