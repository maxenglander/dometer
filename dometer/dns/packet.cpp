#include <arpa/nameser.h>
#include <memory>
#include <stdint.h>
#include <string.h>
#include <utility>

#include "dometer/dns/class.hpp"
#include "dometer/dns/opcode.hpp"
#include "dometer/dns/packet.hpp"
#include "dometer/dns/qr.hpp"
#include "dometer/dns/rcode.hpp"
#include "std/x/expected.hpp"
#include "dometer/util/error.hpp"

using namespace dometer::util;
using namespace std::x;

namespace dometer::dns {
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
        reply.setRCode(RCode::FORMERR);
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

        if(ns_initparse(bytes.get(), size, &handle) < 0) {
            return unexpected<Error>(Error({strerror(errno), errno}));
        }

        return Packet(std::move(bytes), handle, size);
    }

    Packet Packet::notImplemented(const Packet& query) {
        auto reply = copyPacket(query);;
        reply.setQR(QR::REPLY);
        reply.setRCode(RCode::NOTIMP);
        return reply;
    }

    Packet Packet::serverFailure(const Packet& query) {
        auto reply = copyPacket(query);
        reply.setQR(QR::REPLY);
        reply.setRCode(RCode::SERVFAIL);
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

    bool Packet::getAA() const {
        return ns_msg_getflag(handle, ns_f_aa);
    }

    uint16_t Packet::getId() const {
        return ns_msg_id(handle);
    }

    OpCode Packet::getOpCode() const {
        return static_cast<OpCode>(ns_msg_getflag(handle, ns_f_opcode));
    }

    uint16_t Packet::getQDCount() const {
        return ns_msg_count(handle, ns_s_qd);
    }

    QR Packet::getQR() const {
        return static_cast<QR>(ns_msg_getflag(handle, ns_f_qr));
    }

    expected<Question, Error> Packet::getQuestion() const {
        if(getQDCount() != 1)
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

    bool Packet::getRA() const {
        return ns_msg_getflag(handle, ns_f_ra);
    }

    uint8_t Packet::getRCode() const {
        return (uint8_t)ns_msg_getflag(handle, ns_f_rcode);
    }

    bool Packet::getRD() const {
        return ns_msg_getflag(handle, ns_f_rd);
    }

    bool Packet::getTC() const {
        return (bool)ns_msg_getflag(handle, ns_f_tc);
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

    void Packet::setRCode(RCode rcode) {
        // Includes "ra", "z", and "rcode" flags
        uint8_t byte4 = bytes[3];

        // Overwrite "rcode" flag
        byte4 |= static_cast<uint16_t>(rcode) & /*2^4*/0x000f;
        bytes[3] = byte4;
    }

    Packet::operator uint8_t*() const {
        return bytes.get();
    }
}
