#include "dometer/util/lru_map.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::Eq;
using ::testing::MockFunction;

namespace dometer::util {
    class LruMapTest : public ::testing::Test {
        public:
            LruMapTest()
                : _max_size(3),
                  _lru_map(_max_size)
            {}
        protected:
            size_t _max_size;
            lru_map<std::string, std::string> _lru_map;
    };

    TEST_F(LruMapTest, WhenANewKeyIsInserted_NotifiesInsertionListeners) {
        ::testing::MockFunction<void(std::string, std::string)> insertion_listener;
        _lru_map.on_insert(insertion_listener.AsStdFunction());

        EXPECT_CALL(insertion_listener, Call(Eq("hello"), Eq("world"))).Times(1);

        _lru_map.put("hello", "world");
        _lru_map.put("hello", "world");
    }

    TEST_F(LruMapTest, WhenAKeyIsUpdate_NotifiesUpdateListeners) {
        ::testing::MockFunction<void(std::string, std::string, std::string)> update_listener;
        _lru_map.on_update(update_listener.AsStdFunction());

        EXPECT_CALL(update_listener, Call(Eq("hello"), Eq("world"), Eq("worf"))).Times(1);

        _lru_map.put("hello", "world");
        _lru_map.put("hello", "worf");
    }

    TEST_F(LruMapTest, WhenMaxSizeIsReached_NotifiesEvictionListeners) {
        ::testing::MockFunction<void(std::string, std::string)> eviction_listener;
        _lru_map.on_evict(eviction_listener.AsStdFunction());

        EXPECT_CALL(eviction_listener, Call(_, _)).Times(1);

        _lru_map.put("hello", "world");
        _lru_map.put("goodbye", "world");
        _lru_map.put("quux", "baaz");
        _lru_map.put("foo", "bar");
    }

    TEST_F(LruMapTest, WhenMaxSizeIsReached_EvictsLeastRecentlyUsed) {
        ::testing::MockFunction<void(std::string, std::string)> eviction_listener;
        _lru_map.on_evict(eviction_listener.AsStdFunction());

        EXPECT_CALL(eviction_listener, Call(_, _)).Times(0);
        EXPECT_CALL(eviction_listener, Call("goodbye", "world")).Times(1);
        EXPECT_CALL(eviction_listener, Call("quux", "baaz")).Times(1);

        // lru order: ["hello"]
        _lru_map.put("hello", "world");
        // lru order: ["hello", "goodbye"]
        _lru_map.put("goodbye", "world");
        // lru order: ["hello", "goodbye", "quux"]
        _lru_map.put("quux", "baaz");
        // lru order: ["goodbye", "quux", "hello"]
        _lru_map.put("hello", "worf");
        // lru order: ["quux", "hello", "foo"]
        _lru_map.put("foo", "bar");
        // lru order: ["hello", "foo", "goodbye"]
        _lru_map.put("goodbye", "world");
    }
}
