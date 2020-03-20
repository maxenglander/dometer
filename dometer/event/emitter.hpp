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
            emitter(std::vector<callback<T>>);
            emitter(const emitter&);
            virtual void emit(T t);
            virtual void on(callback<T> v);
        private:
            std::vector<callback<T>> callbacks;
    };
}

#include "dometer/event/emitter.ipp"
