#pragma once

#include <memory>
#include <vector>

#include "gmock/gmock.h"
#include "dometer/dns/handler/error.hpp"
#include "dometer/dns/handler/handler.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::dns::handler {
    class mock_handler : public handler {
        public:
            mock_handler() {};
            mock_handler(mock_handler&&) {};
            MOCK_METHOD((std::x::expected<std::vector<uint8_t>, error>), handle, (uint64_t, std::vector<uint8_t>));
    };
}
