#pragma once

#include <memory>
#include <utility>

#include "dometer/util/array_helper.hpp"

namespace dometer::util {
    template <typename T>
    std::unique_ptr<T[]> ArrayHelper::makeUniqueCopy(T* tPtr, size_t size) {
        std::unique_ptr<T[]> ts(new T[size]);
        std::copy(tPtr, tPtr + size, ts.get());
        return std::move(ts);
    }
}
