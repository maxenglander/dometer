#pragma once

#include "network/socket/socket_factory.hpp"
#include "network/socket/unix_socket.hpp"
#include "std/experimental/expected.hpp"

using namespace std::experimental;

namespace Dometer::Network::Socket {
    class SocketFactory {
        public:
            static expected<UnixSocket, std::string> makeUnixSocket();
        private:
            SocketFactory() {};
    };
}
