#pragma once

namespace Dometer::Network::Dns {
    struct Header {
        const bool aa;
        const uint16_t id;
        const uint8_t opcode;
        const uint16_t qdcount;
        const bool ra;
        const uint8_t rcode;
    };
}
