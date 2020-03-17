#pragma once

#include <memory>
#include <vector>

#include "dometer/dns/handler/error.hpp"
#include "std/x/expected.hpp"

namespace dns = dometer::dns;
namespace util = dometer::util;

namespace dometer::dns::handler {
    class handler {
        public:
            virtual std::x::expected<std::vector<uint8_t>, error> handle(uint64_t, std::vector<uint8_t>) = 0;
    };
}
