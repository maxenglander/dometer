#pragma once

#include <arpa/nameser.h>
#include <memory>
#include <stdint.h>

#include "experimental/expected.hpp"
#include "network/dns/header.hpp"
#include "util/error.hpp"

using namespace Dometer::Util;
using namespace std::experimental;

namespace Dometer::Network::Dns {
    class Packet {
        public:
            Packet(const Packet&) = delete;
            Packet(Packet&&);
            ~Packet();
            static expected<Packet, Error> makePacket(uint8_t *bytePtr, size_t size);
            const Header header;
        private:
            Packet(std::unique_ptr<uint8_t[]>, ns_msg, size_t);
            std::unique_ptr<uint8_t[]> bytes;
            ns_msg handle;
            const size_t size;
    };
}
