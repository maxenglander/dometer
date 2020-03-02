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
    class Message {
        public:
            Message(const Message&);
            Message(Message&&);
            ~Message();

            bool getAA() const;
            uint16_t getId() const;
            OpCode getOpCode() const;
            QR getQR() const;
            std::x::expected<Question, util::Error> getQuestion() const;
            bool getRA() const;
            RCode getRCode() const;
            bool getRD() const;
            bool getTC() const;
            void setId(uint16_t id);
            void setQR(QR qr);
            void setRCode(RCode rcode);

            operator uint8_t*() const;

            size_t size() const;
        private:
            Message(std::vector<uint8_t>);
            Message(uint8_t*, size_t);
            Message(std::unique_ptr<uint8_t[]>, size_t);
            Message(std::unique_ptr<uint8_t[]>, ns_msg, size_t);

            uint16_t getQDCount() const;

            std::unique_ptr<uint8_t[]> bytes;
            size_t size_;
            ns_msg handle;

            friend class Factory;
            friend class Parser;
    };
}
