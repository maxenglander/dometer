#include <sys/socket.h>

#include "network/socket/socket_factory.hpp"
#include "network/socket/unix_socket.hpp"
#include "std/experimental/expected.hpp"

using namespace std::experimental;

namespace Dometer::Network::Socket {
    expected<UnixSocket, std::string> SocketFactory::makeUnixSocket() {
        return UnixSocket::makeUnixSocket();
    }
}
