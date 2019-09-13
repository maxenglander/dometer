#include <arpa/nameser.h>
#include <memory>
#include <stdint.h>
#include <string.h>
#include <utility>

#include "experimental/expected.hpp"
#include "network/dns/packet.hpp"
#include "util/error.hpp"

using namespace Dometer::Util;
using namespace std::experimental;

namespace Dometer::Network::Dns {
    Packet::Packet(std::unique_ptr<uint8_t[]> bytes, ns_msg handle, size_t size_)
        : bytes(std::move(bytes)), handle(handle), size_(size_)
    {
    }

    expected<Packet, Error> Packet::makePacket(uint8_t *bytePtr, size_t size) {
        if(size < 0 || size > PACKETSZ)
            return unexpected<Error>(Error{"Invalid packet length: " + std::to_string(size), 0});

        auto bytes = std::make_unique<uint8_t[]>(size);
        std::copy(bytePtr, bytePtr + size, bytes.get());
        ns_msg handle;

        if(ns_initparse(bytes.get(), size, &handle) < 0) 
            return unexpected<Error>(Error({strerror(errno), errno}));

        return Packet(std::move(bytes), handle, size);
    }

    size_t Packet::size() {
        return size_;
    }
}
