#pragma once

#include "dns/class.hpp"
#include "dns/type.hpp"

namespace dometer::dns {
    struct Question {
        std::string qname;
        Type qtype;
        Class qclass;
    };
}
