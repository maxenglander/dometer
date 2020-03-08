#include <arpa/nameser.h>
#include <stdint.h>
#include <string>

#include "dometer/dns/type.hpp"

namespace dometer::dns {
    const type type::a = type(ns_t_a);

    type::type(uint16_t value) : value(value) {}

    type::operator uint16_t() const {
        return value;
    }

    type::operator std::string() const {
        switch(value) {
            case ns_t_a:
                return "A";
            case ns_t_aaaa:
                return "AAAA";
            case ns_t_mx:
                return "MX";
            case ns_t_soa:
                return "SOA";
            case ns_t_cname:
                return "CNAME";
            case ns_t_ptr:
                return "PTR";
            case ns_t_txt:
                return "TXT";
            case ns_t_ns:
                return "NS";
            case ns_t_srv:
                return "SRV";
            //case ns_t_ds:
            //    return "DS";
            case ns_t_any:
                return "ANY";
        }

        return "OTHER";
    }
}
