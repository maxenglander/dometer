#pragma once

#include <functional>
#include <list>
#include <unordered_map>
#include <utility>
#include <vector>

namespace dometer::util {
    template<typename K, typename V>
    class LRUMap {
        using KVNode = typename std::list<std::pair<K, V>>::iterator;

        public:
            LRUMap(size_t maxSize);
            void onEvict(std::function<void(K, V)>);
            void onInsert(std::function<void(K, V)>);
            void put(K, V);
        protected:
            virtual bool shouldEvict();
        private:
            void erase(K);
            void evictOne();
            void insert(K, V);
            void maybeEvict();
            void notifyEvictionListeners(K, V);
            void notifyInsertionListeners(K, V);
            size_t size();

            std::vector<std::function<void(K, V)>> evictionListeners;
            std::vector<std::function<void(K, V)>> insertionListeners;
            std::list<std::pair<K, V>> list;
            std::unordered_map<K, KVNode> map;
            size_t maxSize;
    };
}

#include "dometer/util/lru_map.ipp"
