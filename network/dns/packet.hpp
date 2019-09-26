#pragma once

#include <arpa/nameser.h>
#include <memory>
#include <stdint.h>

#include "experimental/expected.hpp"
#include "network/dns/opcode.hpp"
#include "network/dns/question.hpp"
#include "util/error.hpp"

using namespace Dometer::Util;
using namespace std::experimental;

namespace Dometer::Network::Dns {
    class Packet {
        public:
            static expected<Packet, Error> makePacket(uint8_t *bytePtr, size_t size);
            static expected<Packet, Error> makePacket(std::unique_ptr<uint8_t[]> bytes, size_t size);

            Packet(const Packet&) = delete;
            Packet(Packet&&);
            ~Packet();

            bool aa();
            uint16_t id();
            Opcode opcode();
            uint16_t qdcount();
            bool qr();
            expected<Question, Error> question();
            bool rd();
            bool ra();
            uint8_t rcode();
            bool tc();

            operator void*() const;

            const size_t size;
        private:
            Packet(std::unique_ptr<uint8_t[]>, ns_msg, size_t);

            std::unique_ptr<uint8_t[]> bytes;
            ns_msg handle;
    };
}
