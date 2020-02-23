#pragma once

#include <memory>

namespace dometer::util {
    class ArrayHelper {
        public:
            template <typename T>
            static std::unique_ptr<T[]> makeUniqueCopy(T*, size_t);
    };
}

#include "dometer/util/array_helper.ipp"
