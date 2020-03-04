#pragma once

#include <chrono>
#include <vector>

#include "dometer/dns/question.hpp"
#include "dometer/dns/event/event.hpp"
#include "dometer/dns/event/event_type.hpp"
#include "dometer/dns/resolver/error.hpp"
#include "std/x/expected.hpp"

namespace dometer::dns {
    class Packet;
}

namespace util = dometer::util;

namespace dometer::dns::event {
    class ResolveQueryEvent : public Event {
        public:
            ResolveQueryEvent(
                    const uint64_t sessionId,
                    const dometer::dns::Question question,
                    const std::x::expected<std::vector<uint8_t>, dometer::dns::resolver::Error> resolution,
                    const std::chrono::microseconds duration);
            const std::chrono::microseconds getDuration() const;
            const dns::Question& getQuestion() const;
            const std::x::expected<std::vector<uint8_t>, dometer::dns::resolver::Error>& getResolution() const;
            const uint64_t getSessionId() const;
            EventType getType() const;
        private:
            const uint64_t sessionId;
            const dometer::dns::Question question;
            const std::x::expected<std::vector<uint8_t>, dometer::dns::resolver::Error> resolution;
            const std::chrono::microseconds duration;
    };
}
