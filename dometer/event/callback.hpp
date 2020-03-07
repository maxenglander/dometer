#pragma once

#include <functional>

namespace dometer::event {
    template <typename T>
    using callback = std::function<void(T)>;
}
