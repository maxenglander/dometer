#pragma once

#include "dometer/dns/resolver/libresolv_function.hpp"

namespace dometer::dns::resolver {
    struct libresolv_options {
        const libresolv_function function;
    };
}
