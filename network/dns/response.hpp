#pragma once

#include <vector>

#include "network/dns/answer.hpp"
#include "network/dns/header.hpp"

namespace Dometer::Network::Dns {
    struct Response {
        const Header header;
        const std::vector<Answer> answers;
    };
}
