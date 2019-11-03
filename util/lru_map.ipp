#include <functional>
#include <list>
#include <unordered_map>
#include <vector>

#include "util/lru_map.hpp"

namespace dometer::util {
    template<typename K, typename V>
    LRUMap<K, V>::LRUMap(size_t maxSize) : maxSize(maxSize) {}

    template<typename K, typename V>
    void LRUMap<K, V>::evictOne() {
        auto kvNode = list.back();
        auto key = list.back().first;
        auto value = list.back().second;
        erase(key);
        notifyEvictionListeners(key, value);
    }

    template<typename K, typename V>
    void LRUMap<K, V>::erase(K key) {
        auto kvNode = map[key];
        list.erase(kvNode);
        map.erase(key);
    }

    template<typename K, typename V>
    void LRUMap<K, V>::insert(K key, V value) {
        list.push_front({key, value});
        map[key] = list.begin();
    }

    template<typename K, typename V>
    void LRUMap<K, V>::maybeEvict() {
        while(shouldEvict()) {
            evictOne();
        }
    }

    template<typename K, typename V>
    void LRUMap<K, V>::notifyEvictionListeners(K key, V value) {
        for(auto listener : evictionListeners) {
            listener(key, value);
        }
    }

    template<typename K, typename V>
    void LRUMap<K, V>::notifyInsertionListeners(K key, V value) {
        for(auto listener : insertionListeners) {
            listener(key, value);
        }
    }

    template<typename K, typename V>
    void LRUMap<K, V>::onEvict(std::function<void(K, V)> listener) {
        evictionListeners.push_back(listener);
    }

    template<typename K, typename V>
    void LRUMap<K, V>::onInsert(std::function<void(K, V)> listener) {
        insertionListeners.push_back(listener);
    }

    template<typename K, typename V>
    void LRUMap<K, V>::put(K key, V value) {
        auto search = map.find(key);

        if(search == map.end()) {
            insert(key, value);
            notifyInsertionListeners(key, value);
        } else {
            erase(search->first);
            insert(key, value);
        }

        maybeEvict();
    }

    template<typename K, typename V>
    bool LRUMap<K, V>::shouldEvict() {
        return size() > maxSize;
    }

    template<typename K, typename V>
    size_t LRUMap<K, V>::size() {
        return list.size();
    }
}
