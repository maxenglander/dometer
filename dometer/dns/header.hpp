#pragma once

#include "dometer/dns/opcode.hpp"

namespace dometer::dns {
    struct Header {
        const uint16_t id;
        const bool qr;
        const opcode opcode;
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
