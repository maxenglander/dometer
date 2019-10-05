#pragma once

namespace Dometer::Util {
    template <typename T>
    class Callback {
        virtual void operator()(T t) = 0;
    };
}
