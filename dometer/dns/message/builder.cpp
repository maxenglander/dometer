#include <arpa/inet.h>
#include <arpa/nameser.h>
#include <cerrno>
#include <netinet/in.h>
#include <stdlib.h>
#include <utility>
#include <vector>

#include "dometer/dns/qr.hpp"
#include "dometer/dns/rcode.hpp"
#include "dometer/dns/record.hpp"
#include "dometer/dns/message/builder.hpp"
#include "dometer/dns/message/parser.hpp"

namespace dns = dometer::dns;
namespace util = dometer::util;

namespace dometer::dns::message {
    builder builder::new_builder(const message& source) {
        return builder(source);
    }

    builder::builder(const message& source)
        : _message(source)
    {}

    builder::builder(const builder& _builder)
        : _message(_builder._message),
          _answers(_builder._answers)
    {}

    builder::builder(builder&& _builder)
        : _message(std::move(_builder._message)),
          _answers(std::move(_builder._answers))
    {}

    builder& builder::add_answer(dns::record record) {
        _answers.push_back(record);
        return *this;
    }

    std::x::expected<message, util::error> builder::build() {
        if(_answers.size() == 0)
            return _message;

        _message.set_an_count(_answers.size());
        uint8_t* byte_ptr = (uint8_t*)_message;
        std::vector<uint8_t> bytes(byte_ptr, byte_ptr + _message.size());

        for(auto it = _answers.begin(); it < _answers.end(); it++) {
            auto record = *it;

            if(record.type != dns::type::a) {
                return std::x::unexpected<util::error>(util::error{
                    "Can build messages containing answers of type A only."
                });
            }

            uint8_t cdname[record.name.size()];
            if(ns_name_pton(record.name.c_str(), cdname, sizeof(cdname)) != 0) {
                return std::x::unexpected<util::error>(util::error{
                    "Failed to compress domain name.",
                    std::vector<std::string>({
                        "Domain name: " + record.name
                    }),
                    util::error{
                        strerror(errno),
                        errno
                    }
                });
            }

            uint16_t type = record.type;
            uint16_t class_ = record.class_;
            uint32_t ttl = record.ttl;

            struct in_addr addr;
            inet_aton(record.rdata.c_str(), &addr);
            uint16_t rdlength = sizeof(addr.s_addr);

            uint8_t answer[
                sizeof(cdname)
              + sizeof(type)
              + sizeof(class_)
              + sizeof(ttl)
              + sizeof(rdlength)
              + sizeof(addr.s_addr)
            ];

            int i = 0;
            for(; i < sizeof(cdname); i++) {
                answer[i] = cdname[i];
            }

            answer[i++] = type >> 8;                     // Get upper 8 bits.
            answer[i++] = type & 0xFF;                   // Mask upper 8 bits.

            answer[i++] = class_ >> 8;                   // Get upper 8 bits.
            answer[i++] = class_ & 0xFF;                 // Mask upper 8 bits.

            answer[i++] = ttl >> 24;                     // Get upper 8 bits.
            answer[i++] = (ttl >> 16) & 0xFF;            // Get upper 16 bits, mask upper 8.
            answer[i++] = (ttl >> 24) & 0xFFFF;          // Get upper 24 bits, mask upper 16.
            answer[i++] = ttl & 0xFFFFFF;                // Mask upper 24.

            answer[i++] = rdlength >> 8;                 // Get upper 8 bits.
            answer[i++] = rdlength & 0xFF;               // Mask upper 8 bits.

            answer[i++] = addr.s_addr >> 24;             // Get upper 8 bits.
            answer[i++] = (addr.s_addr >> 16) & 0xFF;    // Get upper 16 bits, mask upper 8.
            answer[i++] = (addr.s_addr >> 24) & 0xFFFF;  // Get upper 24 bits, mask upper 16.
            answer[i++] = addr.s_addr & 0xFFFFFF;        // Mask upper 24.

            for(int i = 0; i < sizeof(answer); i++) {
                bytes.push_back(answer[i]);
            }
        }

        return parser::parse(bytes);
    }

    builder& builder::set_rcode(dns::rcode rcode) {
        _message.set_rcode(rcode);
        return *this;
    }

    builder& builder::set_qr(dns::qr qr) {
        _message.set_qr(qr);
        return *this;
    }
}
