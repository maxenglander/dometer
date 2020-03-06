#pragma once

#include <functional>
#include <memory>
#include <vector>

#include "dometer/event/callback.hpp"

namespace dometer::event {
    template <class T>
    class emitter {
        public:
            emitter();
            emitter(std::vector<Callback<T>>);
            emitter(const emitter&);
            ~emitter();
            void emit(T t);
            void on(Callback<T> v);
        private:
            std::vector<Callback<T>> callbacks;
    };
}

#include "dometer/event/emitter.ipp"
