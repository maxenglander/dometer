#pragma once

#include "dns/class.hpp"
#include "dns/type.hpp"

namespace Dometer::Dns {
    struct Question {
        std::string qname;
        Type qtype;
        Class qclass;
    };
}
