#pragma once

#include <string>

namespace dometer::config::dns::server {
    struct Transport {
        const std::string bindAddress;
        const unsigned int maxConnections;
    };
}
