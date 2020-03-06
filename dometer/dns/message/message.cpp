#include <arpa/nameser.h>
#include <cassert>
#include <iostream>
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
    message::message(const message& _message)
        :   message(std::move(util::ArrayHelper::makeUniqueCopy<uint8_t>(
                _message.bytes.get(), _message.size())), _message.size()
            )
    {
    }

    message::message(message&& message)
        :   bytes(std::move(message.bytes)),
            size_(message.size_),
            handle(message.handle)
    {
        message.handle = {0};
        message.size_ = 0;
    }

    message::message(std::vector<uint8_t> bytes)
        :   message(std::move(util::ArrayHelper::makeUniqueCopy<uint8_t>(bytes.data(), bytes.size())), bytes.size())
    {}

    message::message(uint8_t* bytePtr, size_t size)
        :   message(std::move(util::ArrayHelper::makeUniqueCopy<uint8_t>(bytePtr, size)), size)
    {}

    message::message(std::unique_ptr<uint8_t[]> bytes, size_t size)
        :   bytes(std::move(bytes)),
            size_(size)
    {
        assert(size >= 0 && size <= PACKETSZ);
        assert(ns_initparse(this->bytes.get(), this->size(), &handle) >= 0);
    }

    message::message(std::unique_ptr<uint8_t[]> bytes, ns_msg handle, size_t size)
        :   bytes(std::move(bytes)),
            size_(size),
            handle(handle)
    {}

    message::~message() {
    }

    bool message::getAA() const {
        return ns_msg_getflag(handle, ns_f_aa);
    }

    uint16_t message::getId() const {
        return ns_msg_id(handle);
    }

    OpCode message::getOpCode() const {
        return static_cast<OpCode>(ns_msg_getflag(handle, ns_f_opcode));
    }

    uint16_t message::getQDCount() const {
        return ns_msg_count(handle, ns_s_qd);
    }

    QR message::getQR() const {
        return static_cast<QR>(ns_msg_getflag(handle, ns_f_qr));
    }

    std::x::expected<dometer::dns::question, util::error> message::getQuestion() const {
        if(getQDCount() != 1)
            return std::x::unexpected<util::error>(util::error("message qd count is not equal to 1."));

        ns_rr question;

        ns_msg handle_ = handle;
        if(ns_parserr(&handle_, ns_s_qd, 0, &question) != 0) {
            return std::x::unexpected<util::error>(util::error(
                "Failed to parse DNS question record.",
                util::error(strerror(errno), errno)
            ));
        }
        return dometer::dns::question{
            std::string(ns_rr_name(question)),
            type(ns_rr_type(question)),
            class_(ns_rr_class(question))
        };
    }

    bool message::getRA() const {
        return ns_msg_getflag(handle, ns_f_ra);
    }

    RCode message::getRCode() const {
        return RCode((uint8_t)ns_msg_getflag(handle, ns_f_rcode));
    }

    bool message::getRD() const {
        return ns_msg_getflag(handle, ns_f_rd);
    }

    bool message::getTC() const {
        return (bool)ns_msg_getflag(handle, ns_f_tc);
    }
    void message::setId(uint16_t id) {
        bytes[0] = id >> 8;
        bytes[1] = id & 0xFF;
    }

    void message::setQR(QR qr) {
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

    void message::setRCode(RCode rcode) {
        // Includes "ra", "z", and "rcode" flags
        uint8_t byte4 = bytes[3];

        // Overwrite "rcode" flag
        byte4 |= static_cast<uint16_t>(rcode) & /*2^4*/0x000f;
        bytes[3] = byte4;
    }

    size_t message::size() const {
        return size_;
    };

    message::operator uint8_t*() const {
        return bytes.get();
    }
}
