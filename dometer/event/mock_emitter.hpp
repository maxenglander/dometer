#pragma once

#include "dometer/event/callback.hpp"
#include "dometer/event/emitter.hpp"
#include "gmock/gmock.h"

namespace dometer::event {
    template <class T>
    class mock_emitter : public emitter<T> {
        public:
            MOCK_METHOD(void, emit, (T));
            MOCK_METHOD(void, on, (T));
    };
}
