#pragma once

#include "network/socket/unix_socket.h"
#include "std/experimental/expected.h"

using namespace std::experimental;

namespace DnsTelemeter::Network::Socket {
    class SocketFactory {
        public:
            static expected<UnixSocket, std::string> makeUnixSocket();
        private:
            SocketFactory() {};
    };
}
