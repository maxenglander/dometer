#pragma once

#include "config/dns/resolver/resolver.hpp"
#include "config/dns/server/server.hpp"

namespace dometer::config::dns {
    struct Dns {
        const dometer::config::dns::resolver::Resolver resolver;
        const dometer::config::dns::server::Server server;
    };
}
