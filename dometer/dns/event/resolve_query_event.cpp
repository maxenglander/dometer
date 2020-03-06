#include <vector>

#include "dometer/dns/question.hpp"
#include "dometer/dns/event/resolve_query_event.hpp"
#include "dometer/dns/resolver/error.hpp"
#include "std/x/expected.hpp"

namespace dometer::dns::event {
    resolve_query_event::resolve_query_event(
            const uint64_t session_id,
            const dometer::dns::question question,
            const std::x::expected<std::vector<uint8_t>, dometer::dns::resolver::error> resolution,
            const std::chrono::microseconds duration)
        :   session_id(session_id),
            question(question),
            resolution(resolution),
            duration(duration)
    {}

    const std::chrono::microseconds resolve_query_event::getDuration() const {
        return duration;
    }

    const dometer::dns::question& resolve_query_event::getQuestion() const {
        return question;
    }

    const uint64_t resolve_query_event::getSessionId() const {
        return session_id;
    }

    const std::x::expected<std::vector<uint8_t>, dometer::dns::resolver::error>& resolve_query_event::getResolution() const {
        return resolution;
    }
}
