#pragma once

#include <stddef.h>

namespace Dometer::Util {
    struct EnumHasher {
        template <typename T> size_t operator()(T t) const {
            return static_cast<size_t>(t);
        }
    };
}
