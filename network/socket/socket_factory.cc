#include <sys/socket.h>

#include "network/socket/socket_factory.h"
#include "network/socket/unix_socket.h"
#include "std/experimental/expected.h"

using namespace std::experimental;

namespace DnsTelemeter::Network::Socket {
    expected<::UnixSocket, std::string> SocketFactory::makeUnixSocket() {
        int fd = socket(AF_INET, SOCK_STREAM, 0);
        if(fd < 0) {
            return "Failed to create socket";
        } else {
            return ::makeUnixSocket(fd);
        }
    }

    ::UnixSocket SocketFactory::makeUnixSocket(unsigned int fd) {
        return UnixSocket(fd);
    }
}
