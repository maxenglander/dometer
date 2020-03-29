#include <memory>
#include <vector>

#include "dometer/metrics/example_counter.hpp"
#include "dometer/metrics/handler/prometheus/handler.hpp"
#include "dometer/metrics/handler/prometheus/lru_map.hpp"
#include "prometheus/registry.h"
#include "prometheus/x/types.hpp"
#include "gtest/gtest.h"

namespace dometer::metrics::handler::prometheus {
    class HandlerTest : public ::testing::Test {
        public:
            HandlerTest()
                : _max_size(5),
                  _metric_cache(_max_size),
                  _registry(std::make_shared<::prometheus::Registry>()),
                  _transports(),
                  _handler(_metric_cache, _registry, _transports)
            {}
        protected:
            uint8_t _max_size;
            lru_map _metric_cache;
            std::shared_ptr<::prometheus::Registry> _registry;
            std::vector<std::shared_ptr<::prometheus::x::Transport>> _transports;
            handler _handler;
    };

    TEST_F(HandlerTest, WhenCounterIsIncrementedForFirstTime_ACounterIsAddedToRegistry) {
    }
}
