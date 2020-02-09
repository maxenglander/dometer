#pragma once

#include <string>

#include "config/dns/resolver/libresolv.hpp"
#include "x/optional.hpp"

namespace dometer::config::dns::resolver {
    struct Resolver {
        const std::string type;
        const std::x::optional<Libresolv> libresolv;
    };
}
