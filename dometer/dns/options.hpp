#pragma once

#include "dometer/dns/server/options.hpp"
#include "dometer/dns/resolver/options.hpp"

namespace dometer::dns {
    struct options {
        const dometer::dns::resolver::options resolver;
        const dometer::dns::server::options server;
    };
}
