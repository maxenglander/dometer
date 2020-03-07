#include <functional>
#include <list>
#include <unordered_map>
#include <vector>

#include "dometer/util/lru_map.hpp"

namespace dometer::util {
    template<typename K, typename V>
    lru_map<K, V>::lru_map(size_t max_size) : max_size(max_size) {}

    template<typename K, typename V>
    void lru_map<K, V>::evict_one() {
        auto kv_node = list.back();
        auto key = list.back().first;
        auto value = list.back().second;
        erase(key);
        notify_eviction_listeners(key, value);
    }

    template<typename K, typename V>
    void lru_map<K, V>::erase(K key) {
        auto kv_node = map[key];
        list.erase(kv_node);
        map.erase(key);
    }

    template<typename K, typename V>
    void lru_map<K, V>::insert(K key, V value) {
        list.push_front({key, value});
        map[key] = list.begin();
    }

    template<typename K, typename V>
    void lru_map<K, V>::maybe_evict() {
        while(should_evict()) {
            evict_one();
        }
    }

    template<typename K, typename V>
    void lru_map<K, V>::notify_eviction_listeners(K key, V value) {
        for(auto listener : eviction_listeners) {
            listener(key, value);
        }
    }

    template<typename K, typename V>
    void lru_map<K, V>::notify_insertion_listeners(K key, V value) {
        for(auto listener : insertion_listeners) {
            listener(key, value);
        }
    }

    template<typename K, typename V>
    void lru_map<K, V>::on_evict(std::function<void(K, V)> listener) {
        eviction_listeners.push_back(listener);
    }

    template<typename K, typename V>
    void lru_map<K, V>::on_insert(std::function<void(K, V)> listener) {
        insertion_listeners.push_back(listener);
    }

    template<typename K, typename V>
    void lru_map<K, V>::put(K key, V value) {
        auto search = map.find(key);

        if(search == map.end()) {
            insert(key, value);
            notify_insertion_listeners(key, value);
        } else {
            erase(search->first);
            insert(key, value);
        }

        maybe_evict();
    }

    template<typename K, typename V>
    bool lru_map<K, V>::should_evict() {
        return size() > max_size;
    }

    template<typename K, typename V>
    size_t lru_map<K, V>::size() {
        return list.size();
    }
}
