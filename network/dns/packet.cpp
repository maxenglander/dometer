#include <arpa/nameser.h>
#include <memory>
#include <stdint.h>
#include <string.h>
#include <utility>

#include "experimental/expected.hpp"
#include "network/dns/class.hpp"
#include "network/dns/opcode.hpp"
#include "network/dns/packet.hpp"
#include "util/error.hpp"

using namespace Dometer::Util;
using namespace std::experimental;

namespace Dometer::Network::Dns {
    expected<Packet, Error> Packet::makePacket(uint8_t *bytePtr, size_t size) {
        auto bytes = std::make_unique<uint8_t[]>(size);
        std::copy(bytePtr, bytePtr + size, bytes.get());
        return makePacket(std::move(bytes), size);
    }

    expected<Packet, Error> Packet::makePacket(std::unique_ptr<uint8_t[]> bytes, size_t size) {
        if(size < 0 || size > PACKETSZ)
            return unexpected<Error>(Error{"Invalid packet length: " + std::to_string(size), 0});

        ns_msg handle;

        if(ns_initparse(bytes.get(), size, &handle) < 0)
            return unexpected<Error>(Error({strerror(errno), errno}));

        return Packet(std::move(bytes), handle, size);
    }

    Packet::Packet(Packet&& packet)
        :   size(packet.size),
            bytes(std::move(packet.bytes)),
            handle(std::exchange(packet.handle, {0}))
    {}

    Packet::Packet(std::unique_ptr<uint8_t[]> bytes, ns_msg handle, size_t size)
        :   size(size),
            bytes(std::move(bytes)),
            handle(handle)
    {}

    Packet::~Packet() {}

    bool Packet::aa() {
        return ns_msg_getflag(handle, ns_f_aa);
    }

    uint16_t Packet::id() {
        return ns_msg_id(handle);
    }

    Opcode Packet::opcode() {
        return static_cast<Opcode>(ns_msg_getflag(handle, ns_f_opcode));
    }

    uint16_t Packet::qdcount() {
        return ns_msg_count(handle, ns_s_qd);
    }

    bool Packet::qr() {
        return (bool)ns_msg_getflag(handle, ns_f_qr);
    }

    expected<Question, Error> Packet::question() {
        if(qdcount() != 1)
            return unexpected<Error>(Error{"qdcount is not equal to 1"});

        ns_rr question;

        if(ns_parserr(&handle, ns_s_qd, 0, &question) != 0)
            return unexpected<Error>(Error{strerror(errno), errno});

        return Question{
            std::string(ns_rr_name(question)),
            Type(ns_rr_type(question)),
            Class(ns_rr_class(question))
        };
    }

    bool Packet::ra() {
        return ns_msg_getflag(handle, ns_f_ra);
    }

    uint8_t Packet::rcode() {
        return (uint8_t)ns_msg_getflag(handle, ns_f_rcode);
    }

    bool Packet::rd() {
        return ns_msg_getflag(handle, ns_f_rd);
    }

    bool Packet::tc() {
        return (bool)ns_msg_getflag(handle, ns_f_tc);
    }

    Packet::operator void*() const {
        return bytes.get();
    }
}
