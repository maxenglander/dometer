#pragma once

#include <functional>
#include <memory>
#include <vector>

#include "dometer/event/callback.hpp"

namespace dometer::event {
    template <class T>
    class Emitter {
        public:
            Emitter();
            Emitter(std::vector<Callback<T>>);
            Emitter(const Emitter&);
            ~Emitter();
            void emit(T t);
            void on(Callback<T> v);
        private:
            std::vector<Callback<T>> callbacks;
    };
}

#include "dometer/event/emitter.ipp"
