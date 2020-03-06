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
    emitter<T>::emitter() : emitter<T>(std::vector<Callback<T>>()) {}

    template <class T>
    emitter<T>::emitter(std::vector<Callback<T>> callbacks) : callbacks(callbacks) {}

    template <class T>
    emitter<T>::emitter(const emitter<T>& emitter)
        : emitter<T>::emitter(emitter.callbacks)
    {
    }

    template <class T>
    emitter<T>::~emitter() {
    }


    template <class T>
    void emitter<T>::emit(T t) {
        for(auto it = callbacks.begin(); it != callbacks.end(); it++) {
            Callback<T> callback = *it;
            callback(t);
        }
    }

    template <class T>
    void emitter<T>::on(Callback<T> v) {
        callbacks.push_back(v);
    }
}

#include "dometer/event/emitter.ipp"
