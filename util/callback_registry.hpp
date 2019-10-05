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
            void on(Key k, std::shared_ptr<Callback<T>> v) {
                auto search = map.find(k);

                if(search == map.end()) {
                    map[k] = std::unordered_set<std::shared_ptr<Callback<T>>>();
                }

                std::unordered_set<std::shared_ptr<Callback<T>>> set = map[k];
                set.insert(v);
            }

            void notify(Key k, T t) {
                auto search = map.find(k);

                if(search == map.end()) {
                    return;
                }

                std::unordered_set<std::shared_ptr<Callback<T>>> set = map[k];

                for(auto it = set.begin(); it != set.end(); it++) {
                    std::shared_ptr<Callback<T>> callbackPtr = *it;
                }
            }
        private:
            std::unordered_map<Key, std::unordered_set<std::shared_ptr<Callback<T>>>> map;
    };
}
