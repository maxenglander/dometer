#pragma once

#include "dns/resolver/libresolv_options.hpp"
#include "x/variant.hpp"

using namespace std::x;

namespace dometer::dns::resolver {
    using Options = variant<LibresolvOptions>;
}
