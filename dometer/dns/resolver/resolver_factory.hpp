#pragma once

#include <memory>

#include "dometer/dns/resolver/libresolv_options.hpp"
#include "dometer/dns/resolver/options.hpp"

namespace dometer::dns::resolver {
    class ResolverFactory {
        public:
            static std::shared_ptr<Resolver> makeResolver(LibresolvOptions);
            static std::shared_ptr<Resolver> makeResolver(Options);
    };
}
