#include <arpa/inet.h>
#include <arpa/nameser.h>
#include <cerrno>
#include <cstring>
#include <iostream>
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
    builder builder::new_builder() {
        return builder();
    }

    builder builder::new_builder(const message& source) {
        return builder(source);
    }

    builder::builder()
        : _bytes(12, 0)
    {}

    builder::builder(const message& source)
        : _bytes((uint8_t*)source, (uint8_t*)source + source.size())
    {}

    builder::builder(const builder& _builder)
        : _answers(_builder._answers),
          _bytes(_builder._bytes)
    {}

    builder::builder(builder&& _builder)
        : _answers(std::move(_builder._answers)),
          _bytes(std::move(_builder._bytes))
    {}

    builder& builder::add_answer(dns::record record) {
        _answers.push_back(record);
        return *this;
    }

    std::x::expected<std::vector<uint8_t>, util::error> builder::record_to_bytes(dns::record record) {
        if(record.type != dns::type::a) {
            return std::x::unexpected<util::error>(util::error{
                "Records of type A are supported, other types are not supported."
            });
        }

        uint8_t cdname[MAXCDNAME];
        unsigned char *dnptrs[20], **dpp, **lastdnptr = nullptr;
        lastdnptr = dnptrs + sizeof(dnptrs) / sizeof(dnptrs[0]);
        dpp = dnptrs;
        *dpp++ = cdname;
        *dpp++ = NULL;
        lastdnptr = dnptrs + sizeof(dnptrs) / sizeof(dnptrs[0]);
        int cdnamelen = ns_name_compress(record.name.c_str(), cdname, sizeof(cdname),
                                         (const unsigned char **) dnptrs,
                                         (const unsigned char **) lastdnptr);
        if(cdnamelen < 0) {
            return std::x::unexpected<util::error>(util::error{
                "Could not compress domain name.",
                std::vector<std::string>({ "Domain name: " + record.name }),
                util::error{ strerror(errno), errno }
            });
        }
        std::cout << "Compressed dname, compressed size: " + std::to_string(cdnamelen) << std::endl;

        uint16_t type = record.type;
        uint16_t class_ = record.class_;
        uint32_t ttl = record.ttl;

        struct in_addr addr;
        if(inet_aton(record.rdata.c_str(), &addr) == 0) {
            return std::x::unexpected<util::error>(util::error{
                "Could not convert rdata to inet address.",
                std::vector<std::string>({ "Rdata: " + record.rdata }),
                util::error{ strerror(errno), errno }
            });
        }
        uint16_t rdlength = sizeof(addr.s_addr);

        uint8_t answer[
            sizeof(cdnamelen)
          + sizeof(type)
          + sizeof(class_)
          + sizeof(ttl)
          + sizeof(rdlength)
          + sizeof(addr.s_addr)
        ];

        int i = 0;
        for(; i < cdnamelen; i++) {
            answer[i] = cdname[i];
        }

        ns_put16(type, &answer[i]); i += 2;
        ns_put16(class_, &answer[i]); i += 2;
        ns_put32(ttl, &answer[i]); i += 4;
        ns_put16(rdlength, &answer[i]); i += 2;
        ns_put32(htonl(addr.s_addr), &answer[i]); i += 4;

        return std::vector<uint8_t>(answer, answer + i);
    }

    std::x::expected<message, util::error> builder::build() {
        for(auto it = _answers.begin(); it < _answers.end(); it++) {
            auto answer_bytes_result = record_to_bytes(*it);
            if(!answer_bytes_result) {
                return std::x::unexpected<util::error>(answer_bytes_result.error());
            }
            _bytes.insert(_bytes.end(), answer_bytes_result->begin(), answer_bytes_result->end());

            // Increment and update answer count
            uint16_t an_count = 1 + ns_get16(&_bytes[6]);
            std::cout << "setting answer count to " + std::to_string(an_count) << std::endl;
            ns_put16(an_count, &_bytes[6]);
        }

        std::cout << "Trying to parse message from byte array of size: " + std::to_string(_bytes.size()) << std::endl;
        return parser::parse(_bytes);
    }

    builder& builder::set_id(uint16_t id) {
        ns_put16(id, &_bytes[0]);
        return *this;
    }

    builder& builder::set_rcode(dns::rcode rcode) {
        // Includes "ra", "z", and "rcode" flags
        uint8_t byte = _bytes[3];

        // Overwrite "rcode" flag
        byte |= static_cast<uint16_t>(rcode) & /*2^4*/0x000f;
        _bytes[3] = byte;

        return *this;
    }

    builder& builder::set_qr(dns::qr qr) {
        // Includes "qr", "opcode", "aa" and "tc" flags
        uint8_t byte = _bytes[2];

        // Overwrite "qr" flag
        if(qr == qr::query) {
            byte &= ~(1UL << 7);
        } else {
            byte |= 1UL << 7;
        }

        _bytes[2] = byte;

        return *this;
    }
}
