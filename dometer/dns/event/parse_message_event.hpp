#pragma once

#include "dometer/dns/message/message.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::dns::event {
    class parse_message_event {
        public:
            parse_message_event(const uint64_t session_id, const std::x::expected<dns::message::message, util::error>);
            parse_message_event(const parse_message_event&);
            const std::x::expected<dometer::dns::message::message, util::error>& get_message() const;
            const uint64_t get_session_id() const;
        private:
            const uint64_t session_id;
            const std::x::expected<dns::message::message, util::error> message;
    };
}
