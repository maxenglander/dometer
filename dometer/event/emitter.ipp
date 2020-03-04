#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

#include "dometer/event/callback.hpp"
#include "dometer/event/emitter.hpp"

namespace dometer::event {
    template <class T>
    Emitter<T>::Emitter() : Emitter<T>(std::vector<Callback<T>>()) {}

    template <class T>
    Emitter<T>::Emitter(std::vector<Callback<T>> callbacks) : callbacks(callbacks) {}

    template <class T>
    Emitter<T>::Emitter(const Emitter<T>& emitter)
        : Emitter<T>::Emitter(emitter.callbacks)
    {
        std::cout << "copy-constructed emitter" << std::endl;
    }

    template <class T>
    Emitter<T>::~Emitter() {
        std::cout << "destroyed emitter" << std::endl;
    }


    template <class T>
    void Emitter<T>::emit(T t) {
        for(auto it = callbacks.begin(); it != callbacks.end(); it++) {
            Callback<T> callback = *it;
            callback(t);
        }
    }

    template <class T>
    void Emitter<T>::on(Callback<T> v) {
        callbacks.push_back(v);
    }
}

#include "dometer/event/emitter.ipp"
