#pragma once

#include <stddef.h>

namespace dometer::util {
    struct enum_hasher {
        template <typename T> size_t operator()(T t) const {
            return static_cast<size_t>(t);
        }
    };
}
