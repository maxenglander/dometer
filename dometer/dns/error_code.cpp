#include <arpa/nameser.h>
#include <stdint.h>
#include <string>

#include "dometer/dns/class.hpp"

namespace dometer::dns {
    const dns_class dns_class::IN = dns_class(ns_c_in);

    dns_class::dns_class(uint16_t value) : value(value) {}

    dns_class::operator uint16_t() const {
        return value;
    }

    dns_class::operator std::string() const {
        switch(value) {
            case ns_c_in:
                return "IN";
            case ns_c_chaos:
                return "CH";
            case ns_c_hs:
                return "HS";
        }

        return "other";
    }
}
