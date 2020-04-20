#pragma once

#include <memory>

namespace dometer::util {
    class array_helper {
        public:
            template <typename T>
            static std::unique_ptr<T[]> make_unique_copy(T*, size_t);
    };
}

#include "dometer/util/array_helper.ipp"
