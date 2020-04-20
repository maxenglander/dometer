#pragma once

#include "dometer/dns/record/class.hpp"
#include "dometer/dns/record/type.hpp"

namespace dometer::dns::record {
    struct record {
        std::string name;
        dometer::dns::record::type type;
        dometer::dns::record::class_ class_;
        uint32_t ttl;
        std::string rdata;
    };
}
