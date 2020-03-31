#pragma once

#include <string>

#include "dometer/dns/server/server.hpp"
#include "dometer/util/error.hpp"
#include "gmock/gmock.h"
#include "std/x/expected.hpp"

namespace dometer::dns::server {
    class mock_server : public server {
        public:
            mock_server() {}
            MOCK_METHOD(void, join, ());
            MOCK_METHOD((std::x::expected<void, dometer::util::error>), start, (std::string));
            MOCK_METHOD(void, stop, ());
    };
}
