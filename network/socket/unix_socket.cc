#include <cstring>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "network/socket/unix_socket.h"
#include "std/experimental/expected.h"
#include "util/error/system_exception.h"
#include "util/read_until.h"

using namespace DnsTelemeter::Util::Error;
using namespace std::experimental;

namespace DnsTelemeter::Network::Socket {
    UnixSocket::UnixSocket(unsigned int fd) {
        this->fd = fd;
    }

    UnixSocket::~UnixSocket() {
        ::close(this->fd);
    }

    expected<UnixSocket, std::string> UnixSocket::accept() {
        /******************************************/
        /* Accept an incoming connection          */
        /******************************************/
        int fd = ::accept(this->fd, NULL, NULL);
        if(fd < 0) {
            ::close(fd);
            return unexpected(std::string("Failed to accept client connection"));
        } else {
            return UnixSocket(fd);
        }
    }

    expected<void, std::string> UnixSocket::bind(std::string path) {
        struct sockaddr_un addr;

        /******************************************/
        /* Zero out the server socket address.    */
        /******************************************/
        memset(&addr, 0, sizeof(addr));

        /******************************************/
        /* Set up the UNIX sockaddr structure.    */
        /* by using AF_UNIX for the family and    */
        /* giving it a filepath to bind to.       */
        /*                                        */
        /* Unlink the file so that the bind will  */
        /* succeed, then bind to that file.       */
        /******************************************/
        addr.sun_family = AF_UNIX;
        strncat(addr.sun_path, path.c_str(), sizeof(addr.sun_path) - 1);

        unlink(path.c_str());

        if(::bind(this->fd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
            return unexpected(std::string("Failed to bind socket"));
        }

        return {};
    }

    expected<void, std::string> UnixSocket::listen(size_t maxConnections) {
        /******************************************/
        /* Listen for any client sockets          */
        /******************************************/
        if(::listen(this->fd, maxConnections) < 0) {
            return unexpected(std::string("Failed to listen"));
        }

        return {};
    }

    expected<UnixSocket, std::string> UnixSocket::makeUnixSocket() {
        int fd = socket(AF_INET, SOCK_STREAM, 0);
        if(fd < 0) {
            return unexpected(std::string("Failed to create socket"));
        } else {
            return UnixSocket(fd);
        }
    }

    expected<std::string, std::string> UnixSocket::readUntil(char delimiter, size_t maxBytes) {
        char buffer[maxBytes];
        if(DnsTelemeter::Util::readUntil(this->fd, buffer, delimiter, maxBytes) < 0) {
            return unexpected(std::string("Failed to read delimited line from socket"));
        }
        return std::string(buffer);
    }
}
