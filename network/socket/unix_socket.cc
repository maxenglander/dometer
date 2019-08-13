#include <cstring>
#include <sys/socket.h>
#include <sys/un.h>

#include "network/socket/unix_socket.h"
#include "std/experimental/expected.h"
#include "util/error/system_exception.h"
#include "util/read_until.h"

using DnsTelemeter::Error;
using std::experimental;

namespace DnsTelemeter::Network::Socket {
    UnixSocket::UnixSocket(unsigned int fd) {
        this->fd = fd;
    }

    expected<UnixSocket, std::string> UnixSocket::accept() {
        /******************************************/
        /* Accept an incoming connection          */
        /******************************************/
        int fd = accept(this->fd, NULL, NULL);
        if(fd < 0) {
            close(fd);
            return unexpected("Failed to accept client connection");
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
        strncat(addr.sun_path, address.c_str(), sizeof(addr.sun_path) - 1);

        unlink(path);

        if(bind(addr, (struct sockaddr *) addr, sizeof(addr)) < 0) {
            return unexpected("Failed to bind socket");
        }
    }

    expected<void, std::string> UnixSocket::listen(size_t maxConnections) {
        /******************************************/
        /* Listen for any client sockets          */
        /******************************************/
        if(listen(this->fd, maxConnections) < 0) {
            return unexpected("Failed to listen");
        }
    }

    expected<std::string, std::string> UnixSocket::readUntil(char delimiter, size_t maxBytes) {
        char buffer[maxBytes];
        if(readUntil(this->fd, buffer, delimiter, maxBytes) < 0) {
            return unexpected("Failed to read delimited line from socket");
        } else {
            return std::string(buffer);
        }
    }
}
