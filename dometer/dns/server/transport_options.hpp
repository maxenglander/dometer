#pragma once

#include <string>

namespace dometer::dns::server {
    struct transport_options {
        const std::string bindAddress;
    };
}
