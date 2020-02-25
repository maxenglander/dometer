#pragma once

#include <string>

namespace dometer::dns::server {
    struct TransportOptions {
        const std::string bindAddress;
    };
}
