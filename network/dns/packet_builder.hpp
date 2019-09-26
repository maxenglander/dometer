#pragma once

#include "network/dns/opcode.hpp"

namespace Dometer::Network::Dns {
    class PacketBuilder {
        public:
            PacketBuilder();
            Packet build();
            PacketBuilder& setId(uint16_t);
            PacketBuilder& setOpcode(Opcode);
            PacketBuilder& setRcode(uint16_t);
            PacketBuilder& setQr(bool);
        private:
    }
}
