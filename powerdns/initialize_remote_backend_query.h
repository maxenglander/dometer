#pragma once

#include <string>

namespace DnsTelemeter::PowerDns {
    struct InitializeRemoteBackendQuery {
        const std::string command;
        const int timeout;
    };
}
