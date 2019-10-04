#pragma once

#include <arpa/nameser.h>
#include <memory>
#include <stdint.h>

#include "experimental/expected.hpp"
#include "network/dns/opcode.hpp"
#include "network/dns/qr.hpp"
#include "network/dns/question.hpp"
#include "network/dns/rcode.hpp"
#include "util/error.hpp"

using namespace Dometer::Util;
using namespace std::experimental;

namespace Dometer::Network::Dns {
    class Packet {
        public:
            static Packet copyPacket(const Packet& packet);
            static Packet formatError(const Packet& query); 
            static expected<Packet, Error> makePacket(uint8_t *bytePtr, size_t size);
            static expected<Packet, Error> makePacket(std::unique_ptr<uint8_t[]> bytes, size_t size);
            static Packet notImplemented(const Packet& query); 
            static Packet serverFailure(const Packet& query); 

            Packet(const Packet&);
            Packet(Packet&&);
            ~Packet();

            bool aa() const;
            uint16_t id() const;
            Opcode opcode() const;
            uint16_t qdcount() const;
            QR qr() const;
            expected<Question, Error> question() const;
            bool rd() const;
            bool ra() const;
            uint8_t rcode() const;
            void setId(uint16_t id);
            void setQR(QR qr);
            void setRcode(Rcode rcode);
            bool tc() const;

            operator uint8_t*() const;

            const size_t size;
        private:
            Packet(std::unique_ptr<uint8_t[]>, ns_msg, size_t);

            std::unique_ptr<uint8_t[]> bytes;
            ns_msg handle;
    };
}
