#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

#include "util/callback.hpp"

namespace Dometer::Util {
    template <class Key, class T>
    class CallbackRegistry {
        public:
            CallbackRegistry() : CallbackRegistry(std::unordered_map<Key, std::vector<Callback<T>>>()) {}
            CallbackRegistry(std::unordered_map<Key, std::vector<Callback<T>>> map) : map(map) {}
            void on(Key k, Callback<T> v) {
                auto search = map.find(k);

                if(search == map.end()) {
                    std::cout << "creating new list" << std::endl;
                    map[k] = std::vector<Callback<T>>();
                }

                std::cout << "adding callback" << std::endl;
                map[k].push_back(v);
                std::cout << "list has size: " << map[k].size() << std::endl;
            }

            void notify(Key k, T t) {
                std::cout << "handling notify" << std::endl;
                auto search = map.find(k);
                if(search == map.end()) {
                    return;
                }

                auto list = search->second;
                std::cout << "got callback list of size: " << list.size() << std::endl;
                for(auto it = list.begin(); it != list.end(); it++) {
                    Callback<T> callback = *it;
                    std::cout << "invoking callback" << std::endl;
                    callback(t);
                }
            }
        private:
            std::unordered_map<Key, std::vector<Callback<T>>> map;
    };
}
