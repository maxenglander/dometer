#pragma once

#include "dometer/dns/type.hpp"

namespace dometer::dns {
    struct record {
        std::string name;
        type type;
        std::string rdata;
    };
}
