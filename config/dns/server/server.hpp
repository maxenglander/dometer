#pragma once

#include "config/dns/server/transport.hpp"

namespace dometer::config::dns::server {
    struct Server {
        const Transport transport;
    };
}
