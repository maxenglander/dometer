#include <arpa/nameser.h>
#include <stdint.h>
#include <string>

#include "dometer/dns/class.hpp"

namespace dometer::dns::message {
    const class_ class_::in = class_(ns_c_in);

    class_::class_(uint16_t value) : value(value) {}

    class_::operator uint16_t() const {
        return value;
    }

    class_::operator std::string() const {
        switch(value) {
            case ns_c_in:
                return "IN";
            case ns_c_chaos:
                return "CH";
            case ns_c_hs:
                return "HS";
        }

        return "OTHER";
    }
}
