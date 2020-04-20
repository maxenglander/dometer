#pragma once

#include "dometer/dns/server/transport_options.hpp"

namespace dometer::dns::server {
    struct options {
        const transport_options transport;
    };
}
