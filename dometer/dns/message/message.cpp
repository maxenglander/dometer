#include <arpa/nameser.h>
#include <memory>
#include <stdint.h>
#include <string.h>
#include <utility>

#include "dometer/dns/class.hpp"
#include "dometer/dns/opcode.hpp"
#include "dometer/dns/qr.hpp"
#include "dometer/dns/rcode.hpp"
#include "dometer/dns/message/message.hpp"
#include "dometer/util/array_helper.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"
#include "std/x/unique.hpp"

namespace util = dometer::util;

namespace dometer::dns::message {
    Message Message::copyMessage(const Message& message) {
        std::unique_ptr<uint8_t[]> bytes(new uint8_t[message.size()]);
        uint8_t *bytePtr = message;
        size_t size = message.size();
        std::copy(bytePtr, bytePtr + size, bytes.get());
        return *makeMessage(std::move(bytes), size);
    }

    Message Message::formatError(const Message& message) {
        auto reply = copyMessage(message);
        reply.setQR(QR::REPLY);
        reply.setRCode(RCode::FORMERR);
        return reply;
    }

    std::x::expected<Message, util::Error> Message::makeMessage(uint8_t *bytePtr, size_t size) {
        std::unique_ptr<uint8_t[]> bytes(new uint8_t[size]);
        std::copy(bytePtr, bytePtr + size, bytes.get());
        return makeMessage(std::move(bytes), size);
    }

    std::x::expected<Message, util::Error> Message::makeMessage(std::unique_ptr<uint8_t[]> bytes, size_t size) {
        if(size < 0 || size > PACKETSZ)
            return std::x::unexpected<util::Error>(util::Error{"Invalid message length: " + std::to_string(size), 0});

        ns_msg handle;

        if(ns_initparse(bytes.get(), size, &handle) < 0) {
            return std::x::unexpected<util::Error>(util::Error({strerror(errno), errno}));
        }

        return Message(std::move(bytes), handle, size);
    }

    Message Message::notImplemented(const Message& query) {
        auto reply = copyMessage(query);;
        reply.setQR(QR::REPLY);
        reply.setRCode(RCode::NOTIMP);
        return reply;
    }

    Message Message::serverFailure(const Message& query) {
        auto reply = copyMessage(query);
        reply.setQR(QR::REPLY);
        reply.setRCode(RCode::SERVFAIL);
        return reply;
    }

    Message::Message(const Message& message)
        :   Message(Message::copyMessage(message))
    {}

    Message::Message(Message&& message)
        :   bytes(std::move(message.bytes)),
            size_(message.size_),
            handle(message.handle)
    {
        message.handle = {0};
        message.size_ = 0;
    }

    Message::Message(uint8_t* bytePtr, size_t size)
        :   Message(std::move(util::ArrayHelper::makeUniqueCopy<uint8_t>(bytePtr, size)), size)
    {}

    Message::Message(std::unique_ptr<uint8_t[]> bytes, size_t size)
        :   bytes(std::move(bytes)),
            size_(size)
    {
        if(size < 0 || size > PACKETSZ)
            throw new std::runtime_error("Invalid message length (" + std::to_string(size) + ")");

        if(ns_initparse(bytes.get(), this->size(), &handle) < 0)
            throw new std::runtime_error("Failed to parse bytes into DNS message [" + std::string(strerror(errno)) + "]");
    }

    Message::Message(std::unique_ptr<uint8_t[]> bytes, ns_msg handle, size_t size)
        :   bytes(std::move(bytes)),
            size_(size),
            handle(handle)
    {}

    Message::~Message() {}

    bool Message::getAA() const {
        return ns_msg_getflag(handle, ns_f_aa);
    }

    uint16_t Message::getId() const {
        return ns_msg_id(handle);
    }

    OpCode Message::getOpCode() const {
        return static_cast<OpCode>(ns_msg_getflag(handle, ns_f_opcode));
    }

    uint16_t Message::getQDCount() const {
        return ns_msg_count(handle, ns_s_qd);
    }

    QR Message::getQR() const {
        return static_cast<QR>(ns_msg_getflag(handle, ns_f_qr));
    }

    std::x::expected<Question, util::Error> Message::getQuestion() const {
        if(getQDCount() != 1)
            return std::x::unexpected<util::Error>(util::Error{"qdcount is not equal to 1"});

        ns_rr question;

        ns_msg handle_ = handle;
        if(ns_parserr(&handle_, ns_s_qd, 0, &question) != 0)
            return std::x::unexpected<util::Error>(util::Error{strerror(errno), errno});

        return Question{
            std::string(ns_rr_name(question)),
            Type(ns_rr_type(question)),
            Class(ns_rr_class(question))
        };
    }

    bool Message::getRA() const {
        return ns_msg_getflag(handle, ns_f_ra);
    }

    uint8_t Message::getRCode() const {
        return (uint8_t)ns_msg_getflag(handle, ns_f_rcode);
    }

    bool Message::getRD() const {
        return ns_msg_getflag(handle, ns_f_rd);
    }

    bool Message::getTC() const {
        return (bool)ns_msg_getflag(handle, ns_f_tc);
    }
    void Message::setId(uint16_t id) {
        bytes[0] = id >> 8;
        bytes[1] = id & 0xFF;
    }

    void Message::setQR(QR qr) {
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

    void Message::setRCode(RCode rcode) {
        // Includes "ra", "z", and "rcode" flags
        uint8_t byte4 = bytes[3];

        // Overwrite "rcode" flag
        byte4 |= static_cast<uint16_t>(rcode) & /*2^4*/0x000f;
        bytes[3] = byte4;
    }

    size_t Message::size() const {
        return size_;
    };

    Message::operator uint8_t*() const {
        return bytes.get();
    }
}
