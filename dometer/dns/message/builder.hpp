#pragma once

#include "dometer/dns/message/message.hpp"
#include "dometer/dns/message/qr.hpp"
#include "dometer/dns/message/opcode.hpp"
#include "dometer/dns/message/rcode.hpp"
#include "dometer/dns/message/question.hpp"
#include "dometer/dns/record/record.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace dns = dometer::dns;
namespace util = dometer::util;

namespace dometer::dns::message {
    class builder {
        public:
            builder();
            builder(const builder&);
            builder(builder&&);

            builder& add_answer(dns::record::record);
            builder& add_question(dns::message::question);
            std::x::expected<dns::message::message, util::error> build();
            builder& set_id(uint16_t);
            builder& set_opcode(dns::message::opcode);
            builder& set_qr(dns::message::qr);
            builder& set_rcode(dns::message::rcode);
        private:
            std::x::expected<std::vector<uint8_t>, util::error> question_to_bytes(dns::message::question);
            std::x::expected<std::vector<uint8_t>, util::error> record_to_bytes(dns::record::record);
            std::vector<dns::record::record> _answers;
            std::vector<uint8_t> _bytes;
            std::vector<dns::message::question> _questions;
    };
}
