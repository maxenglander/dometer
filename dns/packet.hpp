#pragma once

#include <arpa/nameser.h>
#include <memory>
#include <stdint.h>

#include "dns/opcode.hpp"
#include "dns/qr.hpp"
#include "dns/question.hpp"
#include "dns/rcode.hpp"
#include "x/expected.hpp"
#include "util/error.hpp"

namespace util = dometer::util;
using namespace std::x;

namespace dometer::dns {
    class Packet {
        public:
            static Packet copyPacket(const Packet& packet);
            static Packet formatError(const Packet& query); 
            static expected<Packet, util::Error> makePacket(uint8_t *bytePtr, size_t size);
            static expected<Packet, util::Error> makePacket(std::unique_ptr<uint8_t[]> bytes, size_t size);
            static Packet notImplemented(const Packet& query); 
            static Packet serverFailure(const Packet& query); 

            Packet(const Packet&);
            Packet(Packet&&);
            ~Packet();

            bool getAA() const;
            uint16_t getId() const;
            OpCode getOpCode() const;
            QR getQR() const;
            expected<Question, util::Error> getQuestion() const;
            bool getRA() const;
            uint8_t getRCode() const;
            bool getRD() const;
            bool getTC() const;
            void setId(uint16_t id);
            void setQR(QR qr);
            void setRCode(RCode rcode);

            operator uint8_t*() const;

            const size_t size;
        private:
            Packet(std::unique_ptr<uint8_t[]>, ns_msg, size_t);

            uint16_t getQDCount() const;

            std::unique_ptr<uint8_t[]> bytes;
            ns_msg handle;
    };
}
