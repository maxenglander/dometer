#pragma once

#include <functional>

namespace dometer::event {
    template <typename T>
    using Callback = std::function<void(T)>;
}
