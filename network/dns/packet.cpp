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

#define DNS_PACKET_HEADER_SIZE 32

using namespace Dometer::Util;
using namespace std::experimental;

namespace Dometer::Network::Dns {
    expected<Packet, Error> Packet::formatError(Packet& packet) {
        uint8_t *bytePtr = (uint8_t*)packet;
        auto reply = makePacket(bytePtr, packet.size);
        if(reply) {
            reply->setQR(QR::REPLY);
            reply->setRcode(Rcode::FORMERR);
        }
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

    expected<Packet, Error> Packet::notImplemented(Packet& query) {
        uint8_t *bytePtr = (uint8_t*)query;
        auto reply = makePacket(bytePtr, query.size);
        if(reply) {
            reply->setQR(QR::REPLY);
            reply->setRcode(Rcode::NOTIMP);
        }
        return reply;
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

    QR Packet::qr() {
        return static_cast<QR>(ns_msg_getflag(handle, ns_f_qr));
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

    bool Packet::tc() {
        return (bool)ns_msg_getflag(handle, ns_f_tc);
    }

    Packet::operator uint8_t*() const {
        return bytes.get();
    }
}
