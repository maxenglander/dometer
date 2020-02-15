#pragma once

#include "dns/resolver/libresolv_function.hpp"

namespace dometer::dns::resolver {
    struct LibresolvOptions {
        const LibresolvFunction function;
    };
}
