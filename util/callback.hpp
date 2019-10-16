#pragma once

#include <functional>

namespace Dometer::Util {
    template <typename T>
    using Callback = std::function<void(T)>;
}
