#include <cassert>
#include <memory>
#include <type_traits>

#include "dometer/dns/resolver/libresolv_options.hpp"
#include "dometer/dns/resolver/libresolv_resolver.hpp"
#include "dometer/dns/resolver/options.hpp"
#include "dometer/dns/resolver/resolver.hpp"
#include "dometer/dns/resolver/resolver_factory.hpp"
#include "std/x/variant.hpp"

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
