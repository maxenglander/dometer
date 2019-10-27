#pragma once

#include "dns/opcode.hpp"

namespace Dometer::Dns {
    struct Header {
        const uint16_t id;
        const bool qr;
        const Opcode opcode;
        const bool aa;
        const bool tc;
        const bool rd;
        const bool ra;
        const uint8_t z;
        const uint8_t rcode;
        const uint16_t qdcount;
        const uint16_t ancount;
        const uint16_t nscount;
        const uint16_t arcount;
    };
}
