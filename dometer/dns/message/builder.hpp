#pragma once

#include "dometer/dns/qr.hpp"
#include "dometer/dns/rcode.hpp"
#include "dometer/dns/record.hpp"
#include "dometer/dns/message/message.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace dns = dometer::dns;
namespace util = dometer::util;

namespace dometer::dns::message {
    class builder {
        public:
            static builder new_builder();
            static builder new_builder(const message&);

            builder();
            builder(const message&);
            builder(const builder&);
            builder(builder&&);

            builder& add_answer(dns::record);
            std::x::expected<message, util::error> build();
            std::x::expected<std::vector<uint8_t>, util::error> record_to_bytes(dns::record);
            builder& set_id(uint16_t);
            builder& set_qr(dns::qr);
            builder& set_rcode(dns::rcode);
        private:
            std::vector<dns::record> _answers;
            std::vector<uint8_t> _bytes;
    };
}
