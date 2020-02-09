#pragma once

#include "config/dns/server/server.hpp"

namespace dometer::config::dns {
    struct Dns {
        const dometer::config::dns::server::Server server;
    };
}
