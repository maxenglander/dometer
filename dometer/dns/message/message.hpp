#pragma once

#include <arpa/nameser.h>
#include <memory>
#include <stdint.h>
#include <vector>

#include "dometer/dns/message/opcode.hpp"
#include "dometer/dns/message/qr.hpp"
#include "dometer/dns/message/question.hpp"
#include "dometer/dns/message/rcode.hpp"
#include "dometer/dns/record/record.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::dns::message {
    class message {
        public:
            message(const message&);
            message(message&&);

            bool get_aa() const;
            uint16_t get_an_count() const;
            std::x::expected<std::vector<dometer::dns::record::record>, util::error> get_answers() const;
            uint16_t get_id() const;
            opcode get_opcode() const;
            uint16_t get_qd_count() const;
            qr get_qr() const;
            std::x::expected<question, util::error> get_question() const;
            bool get_ra() const;
            rcode get_rcode() const;
            bool get_rd() const;
            bool get_tc() const;
            void set_an_count(uint16_t count);
            void set_id(uint16_t id);
            void set_qr(qr qr);
            void set_rcode(rcode rcode);

            operator uint8_t*() const;

            size_t size() const;
        private:
            message(std::vector<uint8_t>);
            message(uint8_t*, size_t);
            message(std::unique_ptr<uint8_t[]>, size_t);
            message(std::unique_ptr<uint8_t[]>, ns_msg, size_t);

            std::unique_ptr<uint8_t[]> bytes;
            size_t size_;
            ns_msg handle;

            friend class factory;
            friend class parser;
    };
}
