#include <cassert>
#include <memory>
#include <type_traits>

#include "dns/resolver/libresolv_options.hpp"
#include "dns/resolver/libresolv_resolver.hpp"
#include "dns/resolver/options.hpp"
#include "dns/resolver/resolver.hpp"
#include "dns/resolver/resolver_factory.hpp"
#include "x/variant.hpp"

namespace dometer::dns::resolver {
    std::shared_ptr<Resolver> ResolverFactory::makeResolver(LibresolvOptions options) {
        return std::make_shared<LibresolvResolver>(options.function);
    }

    std::shared_ptr<Resolver> ResolverFactory::makeResolver(Options options) {
        return std::x::visit(std::x::overloaded(
            [](LibresolvOptions lro) {
                return makeResolver(lro);
            }
        ), options);
    }
}
