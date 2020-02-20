#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include "dometer/util/callback.hpp"

namespace dometer::util {
    template <class Key, class T>
    class CallbackRegistry {
        public:
            CallbackRegistry() : CallbackRegistry(std::unordered_map<Key, std::vector<Callback<T>>>()) {}
            CallbackRegistry(std::unordered_map<Key, std::vector<Callback<T>>> map) : map(map) {}
            void on(Key k, Callback<T> v) {
                auto search = map.find(k);

                if(search == map.end()) {
                    map[k] = std::vector<Callback<T>>();
                }

                map[k].push_back(v);
            }

            void notify(Key k, T t) {
                auto search = map.find(k);
                if(search == map.end()) {
                    return;
                }

                auto list = search->second;
                for(auto it = list.begin(); it != list.end(); it++) {
                    Callback<T> callback = *it;
                    callback(t);
                }
            }
        private:
            std::unordered_map<Key, std::vector<Callback<T>>> map;
    };
}
