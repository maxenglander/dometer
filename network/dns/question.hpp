#pragma once

#include "network/dns/class.hpp"
#include "network/dns/type.hpp"

namespace Dometer::Network::Dns {
    struct Question {
        std::string qname;
        Type qtype;
        Class qclass;
    };
}
