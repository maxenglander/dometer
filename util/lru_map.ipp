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
    LRUMap<K, V>::LRUMap(size_t maxSize, std::function<void(K, V)> onEvict)
            :   LRUMap(maxSize)
    {
        evictionListeners.push_back(onEvict);
    }

    template<typename K, typename V>
    void LRUMap<K, V>::maybeEvict() {
        if(list.size() == 0) return;
        while(list.size() > maxSize) {
            for(auto listener : evictionListeners) {
                auto vNode = list.back();
                map.erase(vNode.first);
                listener(vNode.first, vNode.second);
                list.pop_back();
            }
        }
    }

    template<typename K, typename V>
    void LRUMap<K, V>::onEvict(std::function<void(K, V)> listener) {
        evictionListeners.push_back(listener);
    }

    template<typename K, typename V>
    void LRUMap<K, V>::put(K key, V value) {
        auto search = map.find(key);

        VNode vNode;
        if(search != map.end()) {
            auto vNode = search->second;
            list.erase(vNode);
        }

        list.push_front({key, value});

        map[key] = list.begin();

        maybeEvict();
    }
}
