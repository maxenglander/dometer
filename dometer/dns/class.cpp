#include <arpa/nameser.h>
#include <stdint.h>
#include <string>

#include "dometer/dns/class.hpp"

namespace dometer::dns {
    Class::Class(uint16_t value) : value(value) {}

    Class::operator uint16_t() const {
        return value;
    }

    Class::operator std::string() const {
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
