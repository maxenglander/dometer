#include <cassert>
#include <cstring>
#include <memory>
#include <resolv.h>
#include <type_traits>

#include "dometer/dns/resolver/libresolv_options.hpp"
#include "dometer/dns/resolver/libresolv_resolver.hpp"
#include "dometer/dns/resolver/options.hpp"
#include "dometer/dns/resolver/resolver.hpp"
#include "dometer/dns/resolver/resolver_factory.hpp"
#include "dometer/util/error.hpp"
#include "std/x/variant.hpp"

namespace util = dometer::util;

namespace dometer::dns::resolver {
    std::x::expected<std::shared_ptr<resolver>, util::error> resolver_factory::make_resolver(libresolv_options options) {
        struct __res_state stat;
        if(res_ninit(&stat) < 0) {
            return std::x::unexpected<util::error>(util::error{
                "Failed to initialize resolver state.",
                util::error{
                    strerror(errno),
                    errno
                }
            });
        }

        return std::make_shared<libresolv_resolver>(options.function, stat);
    }

    std::x::expected<std::shared_ptr<resolver>, util::error> resolver_factory::make_resolver(options _options) {
        return std::x::visit(std::x::overloaded(
            [](libresolv_options lro) {
                return make_resolver(lro);
            }
        ), _options);
    }
}
