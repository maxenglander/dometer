#pragma once

#include <memory>
#include <vector>

#include "dometer/dns/handler/handler.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::dns::handler {
    class mock_handler : public handler {
        public:
            mock_handler(const mock_handler&) = delete;
            mock_handler(mock_handler&&);
            std::x::expected<std::vector<uint8_t>, util::error> handle(uint64_t, std::vector<uint8_t>);
