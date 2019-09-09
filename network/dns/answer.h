#pragma once

#include <string>

namespace Dometer::Network::Dns {
    struct Answer {
        const std::string name;
        const std::string type;
        const std::string content;
        const unsigned int ttl;
    };
}
