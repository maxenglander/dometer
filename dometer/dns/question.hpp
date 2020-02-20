#pragma once

#include "dometer/dns/class.hpp"
#include "dometer/dns/type.hpp"

namespace dometer::dns {
    struct Question {
        std::string qname;
        Type qtype;
        Class qclass;
    };
}
