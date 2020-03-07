#pragma once

#include <arpa/nameser.h>
#include <memory>
#include <stdint.h>

#include "dometer/dns/opcode.hpp"
#include "dometer/dns/qr.hpp"
#include "dometer/dns/question.hpp"
#include "dometer/dns/rcode.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

namespace util = dometer::util;

namespace dometer::dns::message {
    class message {
        public:
            message(const message&);
            message(message&&);
            ~message();

            bool get_aa() const;
            uint16_t get_id() const;
            opcode get_opcode() const;
            qr get_qr() const;
            std::x::expected<question, util::error> get_question() const;
            bool get_ra() const;
            rcode get_rcode() const;
            bool get_rd() const;
            bool get_tc() const;
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

            uint16_t get_qd_count() const;

            std::unique_ptr<uint8_t[]> bytes;
            size_t size_;
            ns_msg handle;

            friend class factory;
            friend class parser;
    };
}
