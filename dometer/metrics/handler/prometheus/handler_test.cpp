#include <vector>

#include "dometer/metrics/handler/prometheus/handler.hpp"
#include "gtest/gtest.h"

namespace dometer::metrics::handler::prometheus {
    class HandlerTest : public ::testing::Test {
        public:
            HandlerTest()
            {}
        protected:
            handler _handler;
    };
}
