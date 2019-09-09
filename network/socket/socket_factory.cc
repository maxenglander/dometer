#include <sys/socket.h>

#include "network/socket/socket_factory.h"
#include "network/socket/unix_socket.h"
#include "std/experimental/expected.h"

using namespace std::experimental;

namespace Dometer::Network::Socket {
    expected<UnixSocket, std::string> SocketFactory::makeUnixSocket() {
        return UnixSocket::makeUnixSocket();
    }
}
