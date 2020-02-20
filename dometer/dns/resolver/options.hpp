#pragma once

#include "dometer/dns/resolver/libresolv_options.hpp"
#include "std/x/variant.hpp"

using namespace std::x;

namespace dometer::dns::resolver {
    using Options = variant<LibresolvOptions>;
}
