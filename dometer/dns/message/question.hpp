#pragma once

#include "dometer/dns/record/class.hpp"
#include "dometer/dns/record/type.hpp"

namespace dometer::dns::message {
    struct question {
        std::string qname;
        dometer::dns::record::type qtype;
        dometer::dns::record::class_ qclass;
    };
}
