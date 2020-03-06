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
    std::shared_ptr<Resolver> resolver_factory::make_resolver(libresolv_options options) {
        return std::make_shared<LibresolvResolver>(options.function);
    }

    std::shared_ptr<Resolver> resolver_factory::make_resolver(options options) {
        return std::x::visit(std::x::overloaded(
            [](libresolv_options lro) {
                return make_resolver(lro);
            }
        ), options);
    }
}
