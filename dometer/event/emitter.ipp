#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include "dometer/event/callback.hpp"
#include "dometer/event/emitter.hpp"

namespace dometer::event {
    template <class Key, class T>
    Emitter<Key, T>::Emitter() : Emitter<Key, T>(std::unordered_map<Key, std::vector<Callback<T>>>()) {}

    template <class Key, class T>
    Emitter<Key, T>::Emitter(std::unordered_map<Key, std::vector<Callback<T>>> map) : map(map) {}

    template <class Key, class T>
    void Emitter<Key, T>::emit(Key k, T t) {
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

    template <class Key, class T>
    void Emitter<Key, T>::on(Key k, Callback<T> v) {
        auto search = map.find(k);

        if(search == map.end()) {
            map[k] = std::vector<Callback<T>>();
        }

        map[k].push_back(v);
    }
}

#include "dometer/event/emitter.ipp"
