#pragma once

#include <functional>

namespace dometer::util {
    template <typename T>
    using Callback = std::function<void(T)>;
}
