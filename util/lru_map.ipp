#include <functional>
#include <list>
#include <unordered_map>
#include <vector>

#include "util/lru_map.hpp"

namespace Dometer::Util {
    template<typename K, typename V>
    LRUMap<K, V>::LRUMap(size_t maxSize)
            :   maxSize(maxSize)
    {}

    template<typename K, typename V>
    LRUMap<K, V>::LRUMap(size_t maxSize, std::function<void(std::pair<K, V>)> onEvict)
            :   LRUMap(maxSize)
    {
        evictionListeners.push_back(onEvict);
    }

    template<typename K, typename V>
    void LRUMap<K, V>::maybeEvict() {
        while(list.size() > maxSize) {
            for(auto listener : evictionListeners) {
                auto kv = list.pop_front();
                map.erase(kv.first);
                listener(kv);
            }
        }
    }

    template<typename K, typename V>
    void LRUMap<K, V>::onEvict(std::function<void(std::pair<K, V>)> listener) {
        evictionListeners.push_back(listener);
    }

    template<typename K, typename V>
    void LRUMap<K, V>::put(K key, V value) {
        auto search = map.find(key);

        VNode vNode = NULL;
        if(search != map.end()) {
            vNode = search->second;
            list.erase(vNode);
        } else {
            vNode(key, value);
        }

        list.push_back(vNode);

        maybeEvict();
    }
}
