#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "util/callback.hpp"

namespace Dometer::Util {
    template <
        class Key,
        class T
    >
    class CallbackRegistry {
        public:
            CallbackRegistry() : CallbackRegistry(std::unordered_map<Key, std::unordered_set<std::shared_ptr<Callback<T>>>>()) {}
            CallbackRegistry(std::unordered_map<Key, std::unordered_set<std::shared_ptr<Callback<T>>>> map) : map(map) {}
            void insert(Key k, std::shared_ptr<Callback<T>> v) {
                auto search = this->map.find(k);

                if(search == this->map.end()) {
                    this->map[k] = std::unordered_set<std::shared_ptr<Callback<T>>>();
                }

                std::unordered_set<std::shared_ptr<Callback<T>>> set = this->map[k];
                set.insert(v);
            }
        private:
            std::unordered_map<Key, std::unordered_set<std::shared_ptr<Callback<T>>>> map;
    };
}
