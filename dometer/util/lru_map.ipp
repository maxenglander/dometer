#include <functional>
#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>

namespace dometer::util {
    template<typename K, typename V>
    lru_map<K, V>::lru_map(size_t max_size) : max_size(max_size) {}

    template<typename K, typename V>
    lru_map<K, V>::lru_map(const lru_map& src)
        : eviction_listeners(src.eviction_listeners),
          insertion_listeners(src.insertion_listeners),
          update_listeners(src.update_listeners),
          list(src.list),
          map(src.map),
          max_size(src.max_size)
    {}


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
    void lru_map<K, V>::notify_update_listeners(K key, V old_value, V value) {
        for(auto listener : update_listeners) {
            listener(key, old_value, value);
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
    void lru_map<K, V>::on_update(std::function<void(K, V, V)> listener) {
        update_listeners.push_back(listener);
    }

    template<typename K, typename V>
    void lru_map<K, V>::put(K key, V value) {
        auto search = map.find(key);

        if(search == map.end()) {
            insert(key, value);
            notify_insertion_listeners(key, value);
        } else {
            erase(search->first);
            auto old_value = search->second->second;
            insert(key, value);
            notify_update_listeners(key, old_value, value);
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
