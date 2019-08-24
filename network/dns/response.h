#pragma once

#include <vector>

#include "network/dns/answer.h"
#include "network/dns/header.h"

namespace DnsTelemeter::Network::Dns {
    struct Response {
        const Header header;
        const std::vector<Answer> answers;
    };
}
