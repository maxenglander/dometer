#pragma once

#include "dometer/dns/class.hpp"
#include "dometer/dns/type.hpp"

namespace dometer::dns {
    struct question {
        std::string qname;
        type qtype;
        dns_class qclass;
    };
}
