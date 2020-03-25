#pragma once

#include <functional>
#include <list>
#include <unordered_map>
#include <utility>
#include <vector>

namespace dometer::util {
    template<typename K, typename V>
    class lru_map {
        using kv_node = typename std::list<std::pair<K, V>>::iterator;

        public:
            lru_map(size_t max_size);
            lru_map(const lru_map&);
            lru_map(lru_map&&) = delete;
            void on_evict(std::function<void(K, V)>);
            void on_insert(std::function<void(K, V)>);
            void put(K, V);
        protected:
            virtual bool should_evict();
        private:
            void erase(K);
            void evict_one();
            void insert(K, V);
            void maybe_evict();
            void notify_eviction_listeners(K, V);
            void notify_insertion_listeners(K, V);
            size_t size();

            std::vector<std::function<void(K, V)>> eviction_listeners;
            std::vector<std::function<void(K, V)>> insertion_listeners;
            std::list<std::pair<K, V>> list;
            std::unordered_map<K, kv_node> map;
            size_t max_size;
    };
}

#include "dometer/util/lru_map.ipp"
