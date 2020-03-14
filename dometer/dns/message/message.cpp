#include <arpa/inet.h>
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
#include "dometer/dns/record.hpp"
#include "dometer/dns/message/message.hpp"
#include "dometer/util/array_helper.hpp"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"
#include "std/x/unique.hpp"

namespace util = dometer::util;

namespace dometer::dns::message {
    message::message(const message& _message)
        :   message(std::move(util::array_helper::make_unique_copy<uint8_t>(
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
        :   message(std::move(util::array_helper::make_unique_copy<uint8_t>(bytes.data(), bytes.size())), bytes.size())
    {}

    message::message(uint8_t* byte_ptr, size_t size)
        :   message(std::move(util::array_helper::make_unique_copy<uint8_t>(byte_ptr, size)), size)
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

    bool message::get_aa() const {
        return ns_msg_getflag(handle, ns_f_aa);
    }

    uint16_t message::get_an_count() const {
        return ns_msg_count(handle, ns_s_an);
    }

    std::x::expected<std::vector<dometer::dns::record>, util::error> message::get_answers() const {
        std::vector<dometer::dns::record> answers;

        ns_msg handle_ = handle;
        for(int i = 0; i < get_an_count(); i++) {
            ns_rr answer;

            if(ns_parserr(&handle_, ns_s_an, i, &answer) != 0) {
                return std::x::unexpected<util::error>(util::error(
                    "Failed to parse DNS answer record.",
                    util::error(strerror(errno), errno)
                ));
            }

            answers.push_back(dometer::dns::record{
                std::string(ns_rr_name(answer)),
                dometer::dns::type(ns_rr_type(answer)),
                dometer::dns::class_(ns_rr_class(answer)),
                ns_rr_ttl(answer),
                std::string(inet_ntoa(*(struct in_addr*)ns_rr_rdata(answer)))
            });
        }

        return answers;
    }

    uint16_t message::get_id() const {
        return ns_msg_id(handle);
    }

    opcode message::get_opcode() const {
        return static_cast<opcode>(ns_msg_getflag(handle, ns_f_opcode));
    }

    uint16_t message::get_qd_count() const {
        return ns_msg_count(handle, ns_s_qd);
    }

    qr message::get_qr() const {
        return static_cast<qr>(ns_msg_getflag(handle, ns_f_qr));
    }

    std::x::expected<dometer::dns::question, util::error> message::get_question() const {
        if(get_qd_count() != 1)
            return std::x::unexpected<util::error>(util::error("Message qd count is not equal to 1."));

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

    bool message::get_ra() const {
        return ns_msg_getflag(handle, ns_f_ra);
    }

    rcode message::get_rcode() const {
        return rcode((uint8_t)ns_msg_getflag(handle, ns_f_rcode));
    }

    bool message::get_rd() const {
        return ns_msg_getflag(handle, ns_f_rd);
    }

    bool message::get_tc() const {
        return (bool)ns_msg_getflag(handle, ns_f_tc);
    }

    void message::set_an_count(uint16_t count) {
        bytes[6] = count >> 8;
        bytes[7] = count & 0xFF;
    }

    void message::set_id(uint16_t id) {
        bytes[0] = id >> 8;
        bytes[1] = id & 0xFF;
    }

    void message::set_qr(qr qr) {
        // Includes "qr", "opcode", "aa" and "tc" flags
        uint8_t byte3 = bytes[2];

        // Overwrite "qr" flag
        if(qr == qr::query) {
            byte3 &= ~(1UL << 7);
        } else {
            byte3 |= 1UL << 7;
        }

        bytes[2] = byte3;
    }

    void message::set_rcode(rcode rcode) {
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
