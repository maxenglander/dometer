#include <arpa/nameser.h>
#include <memory>
#include <stdint.h>
#include <string.h>
#include <utility>

#include "experimental/expected.hpp"
#include "network/dns/class.hpp"
#include "network/dns/opcode.hpp"
#include "network/dns/packet.hpp"
#include "network/dns/qr.hpp"
#include "network/dns/rcode.hpp"
#include "util/error.hpp"

using namespace Dometer::Util;
using namespace std::experimental;

namespace Dometer::Network::Dns {
    Packet Packet::copyPacket(const Packet& packet) {
        auto bytes = std::make_unique<uint8_t[]>(packet.size);
        uint8_t *bytePtr = packet;
        size_t size = packet.size;
        std::copy(bytePtr, bytePtr + size, bytes.get());
        return *makePacket(std::move(bytes), packet.size);
    }

    Packet Packet::formatError(const Packet& packet) {
        auto reply = copyPacket(packet);
        reply.setQR(QR::REPLY);
        reply.setRcode(Rcode::FORMERR);
        return reply;
    }

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

    Packet Packet::notImplemented(const Packet& query) {
        auto reply = copyPacket(query);;
        reply.setQR(QR::REPLY);
        reply.setRcode(Rcode::NOTIMP);
        return reply;
    }

    Packet Packet::serverFailure(const Packet& query) {
        auto reply = copyPacket(query);
        reply.setQR(QR::REPLY);
        reply.setRcode(Rcode::SERVFAIL);
        return reply;
    }

    Packet::Packet(const Packet& packet)
        :   Packet(Packet::copyPacket(packet))
    {}

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

    bool Packet::aa() const {
        return ns_msg_getflag(handle, ns_f_aa);
    }

    uint16_t Packet::id() const {
        return ns_msg_id(handle);
    }

    Opcode Packet::opcode() const {
        return static_cast<Opcode>(ns_msg_getflag(handle, ns_f_opcode));
    }

    uint16_t Packet::qdcount() const {
        return ns_msg_count(handle, ns_s_qd);
    }

    QR Packet::qr() const {
        return static_cast<QR>(ns_msg_getflag(handle, ns_f_qr));
    }

    expected<Question, Error> Packet::question() const {
        if(qdcount() != 1)
            return unexpected<Error>(Error{"qdcount is not equal to 1"});

        ns_rr question;

        ns_msg handle_ = handle;
        if(ns_parserr(&handle_, ns_s_qd, 0, &question) != 0)
            return unexpected<Error>(Error{strerror(errno), errno});

        return Question{
            std::string(ns_rr_name(question)),
            Type(ns_rr_type(question)),
            Class(ns_rr_class(question))
        };
    }

    bool Packet::ra() const {
        return ns_msg_getflag(handle, ns_f_ra);
    }

    uint8_t Packet::rcode() const {
        return (uint8_t)ns_msg_getflag(handle, ns_f_rcode);
    }

    bool Packet::rd() const {
        return ns_msg_getflag(handle, ns_f_rd);
    }

    void Packet::setId(uint16_t id) {
        bytes[0] = id >> 8;
        bytes[1] = id & 0xFF;
    }

    void Packet::setQR(QR qr) {
        // Includes "qr", "opcode", "aa" and "tc" flags
        uint8_t byte3 = bytes[2];

        // Overwrite "qr" flag
        if(qr == QR::QUERY) {
            byte3 &= ~(1UL << 7);
        } else {
            byte3 |= 1UL << 7;
        }

        bytes[2] = byte3;
    }

    void Packet::setRcode(Rcode rcode) {
        // Includes "ra", "z", and "rcode" flags
        uint8_t byte4 = bytes[3];

        // Overwrite "rcode" flag
        byte4 |= static_cast<uint16_t>(rcode) & /*2^4*/0x000f;
        bytes[3] = byte4;
    }

    bool Packet::tc() const {
        return (bool)ns_msg_getflag(handle, ns_f_tc);
    }

    Packet::operator uint8_t*() const {
        return bytes.get();
    }
}
