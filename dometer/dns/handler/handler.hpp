#pragma once

#include <memory>
#include <vector>

#include "std/x/expected.hpp"
#include "dometer/util/error.hpp"

namespace dns = dometer::dns;
namespace util = dometer::util;

namespace dometer::dns::handler {
    class Handler {
        public:
            virtual std::x::expected<std::vector<uint8_t>, util::error> handle(uint64_t, std::vector<uint8_t>) = 0;
    };
}
