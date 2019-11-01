#pragma once

#include <functional>
#include <list>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Dometer::Util {
    template<typename K, typename V>
    class LRUMap {
        using VNode = typename std::list<std::pair<K, V>>::iterator;

        public:
            LRUMap(size_t maxSize);
            LRUMap(size_t maxSize, std::function<void(K, V)> onEvict);
            void onEvict(std::function<void(K, V)>);
            void put(K, V);
        private:
            void maybeEvict();
            std::vector<std::function<void(K, V)>> evictionListeners;
            std::list<std::pair<K, V>> list;
            std::unordered_map<K, VNode> map;
            size_t maxSize;
    };
}

#include "util/lru_map.ipp"
