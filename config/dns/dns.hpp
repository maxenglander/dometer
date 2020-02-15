#pragma once

#include "dns/resolver/options.hpp"
#include "config/dns/server/server.hpp"

namespace dometer::config::dns {
    struct Dns {
        const dometer::dns::resolver::Options resolver;
        const dometer::config::dns::server::Server server;
    };
}
