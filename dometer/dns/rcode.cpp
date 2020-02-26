#include <arpa/nameser.h>
#include <stdint.h>
#include <string>

#include "dometer/dns/rcode.hpp"

namespace dometer::dns {
    const RCode RCode::NOERROR = RCode(0);
    const RCode RCode::FORMERR = RCode(1);
    const RCode RCode::SERVFAIL = RCode(2);
    const RCode RCode::NXDOMAIN = RCode(3);
    const RCode RCode::NOTIMPL = RCode(4);
    const RCode RCode::REFUSED = RCode(5);

    RCode::RCode(uint8_t value) : value(value) {}

    RCode::operator uint8_t() const {
        return value;
    }

    RCode::operator std::string() const {
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
