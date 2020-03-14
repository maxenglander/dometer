#pragma once

#include "dometer/dns/class.hpp"
#include "dometer/dns/type.hpp"

namespace dometer::dns {
    struct record {
        std::string name;
        dometer::dns::type type;
        dometer::dns::class_ class_;
        uint32_t ttl;
        std::string rdata;
    };
}
