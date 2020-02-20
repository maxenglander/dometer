#pragma once

#include "dometer/dns/resolver/options.hpp"
#include "dometer/config/dns/server/server.hpp"

namespace dometer::config::dns {
    struct Dns {
        const dometer::dns::resolver::Options resolver;
        const dometer::config::dns::server::Server server;
    };
}
