#include <sys/socket.h>

#include "network/socket/unix_socket.h"
#include "util/error/system_exception.h"

using DnsTelemeter::Error;

namespace DnsTelemeter::Network::Socket {
    UnixSocket::UnixSocket() {
        if(this->fd = socket(AF_UNIX, SOCK_STREAM, 0) < 0) {
            throw SystemException("Failed to create a new unix domain socket", errno);
        }
    }
}
