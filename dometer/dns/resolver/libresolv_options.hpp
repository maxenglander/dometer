#pragma once

#include "dometer/dns/resolver/libresolv_function.hpp"

namespace dometer::dns::resolver {
    struct LibresolvOptions {
        const LibresolvFunction function;
    };
}
