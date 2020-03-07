#pragma once

#include <cassert>
#include <memory>
#include <utility>

#include "dometer/util/array_helper.hpp"

namespace dometer::util {
    template <typename T>
    std::unique_ptr<T[]> array_helper::make_unique_copy(T* t_ptr, size_t size) {
        std::unique_ptr<T[]> ts(new T[size]);
        std::copy(t_ptr, t_ptr + size, ts.get());
        return std::move(ts);
    }
}
