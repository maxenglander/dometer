#pragma once

#include <chrono>
#include <vector>

#include "dometer/dns/question.hpp"
#include "dometer/dns/resolver/error.hpp"
#include "std/x/expected.hpp"

namespace dometer::dns {
    class Packet;
}

namespace util = dometer::util;

namespace dometer::dns::event {
    class resolve_query_event {
        public:
            resolve_query_event(
                    const uint64_t session_id,
                    const dometer::dns::question question,
                    const std::x::expected<std::vector<uint8_t>, dometer::dns::resolver::error> resolution,
                    const std::chrono::microseconds duration);
            const std::chrono::microseconds getDuration() const;
            const dns::question& getQuestion() const;
            const std::x::expected<std::vector<uint8_t>, dometer::dns::resolver::error>& getResolution() const;
            const uint64_t getSessionId() const;
        private:
            const uint64_t session_id;
            const dometer::dns::question question;
            const std::x::expected<std::vector<uint8_t>, dometer::dns::resolver::error> resolution;
            const std::chrono::microseconds duration;
    };
}
