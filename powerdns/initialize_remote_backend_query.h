#pragma once

#include <string>

namespace Dometer::PowerDns {
    struct InitializeRemoteBackendQuery {
        const std::string command;
        const int timeout;
    };
}
