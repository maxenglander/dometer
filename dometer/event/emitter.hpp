#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include "dometer/event/callback.hpp"

namespace dometer::event {
    template <class Key, class T>
    class Emitter {
        public:
            Emitter();
            Emitter(std::unordered_map<Key, std::vector<Callback<T>>> map);
            void emit(Key k, T t);
            void on(Key k, Callback<T> v);
        private:
            std::unordered_map<Key, std::vector<Callback<T>>> map;
    };
}

#include "dometer/event/emitter.ipp"
