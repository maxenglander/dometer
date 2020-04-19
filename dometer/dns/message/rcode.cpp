#include <arpa/nameser.h>
#include <stdint.h>
#include <string>

#include "dometer/dns/message/rcode.hpp"

namespace dometer::dns::message {
    const rcode rcode::noerror = rcode(0);
    const rcode rcode::formerr = rcode(1);
    const rcode rcode::servfail = rcode(2);
    const rcode rcode::nxdomain = rcode(3);
    const rcode rcode::notimpl = rcode(4);
    const rcode rcode::refused = rcode(5);

    rcode::rcode(uint8_t value) : value(value) {}

    rcode::operator uint8_t() const {
        return value;
    }

    rcode::operator std::string() const {
        switch(value) {
            case 0:
                return "NOERROR";
            case 1:
                return "FORMERR";
            case 2:
                return "SERVFAIL";
            case 3:
                return "NXDOMAIN";
            case 4:
                return "NOTIMPL";
            case 5:
                return "REFUSED";
            case 6:
                return "YXDOMAIN";
            case 7:
                return "YXRRSET";
            case 8:
                return "NXRRSET";
            case 9:
                return "NOTAUTH";
            case 10:
                return "NOTZONE";
            case 11:
                return "DSOTYPENI";
            case 12:
            case 13:
            case 14:
            case 15:
                return "UNASSIGNED";
        }

        return "OTHER";
    }
}
