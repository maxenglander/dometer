#pragma once

#include <chrono>
#include <vector>

#include "dometer/dns/question.hpp"
#include "dometer/dns/resolver/error.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::dns::event {
    class resolve_query_event {
        public:
            resolve_query_event(
                    const uint64_t session_id,
                    const dometer::dns::question question,
                    const std::x::expected<std::vector<uint8_t>, dometer::dns::resolver::error> resolution,
                    const std::chrono::microseconds duration);
            const std::chrono::microseconds get_duration() const;
            const dns::question& get_question() const;
            const std::x::expected<std::vector<uint8_t>, dometer::dns::resolver::error>& get_resolution() const;
            const uint64_t get_session_id() const;
        private:
            const uint64_t session_id;
            const dometer::dns::question question;
            const std::x::expected<std::vector<uint8_t>, dometer::dns::resolver::error> resolution;
            const std::chrono::microseconds duration;
    };
}
