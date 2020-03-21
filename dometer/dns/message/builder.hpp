#pragma once

#include "dometer/dns/qr.hpp"
#include "dometer/dns/opcode.hpp"
#include "dometer/dns/rcode.hpp"
#include "dometer/dns/record.hpp"
#include "dometer/dns/question.hpp"
#include "dometer/dns/message/message.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace dns = dometer::dns;
namespace util = dometer::util;

namespace dometer::dns::message {
    class builder {
        public:
            static builder new_builder();

            builder();
            builder(const builder&);
            builder(builder&&);

            builder& add_answer(dns::record);
            builder& add_question(dns::question);
            std::x::expected<message, util::error> build();
            builder& set_id(uint16_t);
            builder& set_opcode(dns::opcode);
            builder& set_qr(dns::qr);
            builder& set_rcode(dns::rcode);
        private:
            std::x::expected<std::vector<uint8_t>, util::error> question_to_bytes(dns::question);
            std::x::expected<std::vector<uint8_t>, util::error> record_to_bytes(dns::record);
            std::vector<dns::record> _answers;
            std::vector<uint8_t> _bytes;
            std::vector<dns::question> _questions;
    };
}
