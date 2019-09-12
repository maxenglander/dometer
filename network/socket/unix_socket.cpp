#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "network/socket/recv_until.hpp"
#include "network/socket/unix_socket.hpp"
#include "std/experimental/expected.hpp"
#include "util/error.hpp"

using namespace std::experimental;

namespace Dometer::Network::Socket {
    UnixSocket::UnixSocket(int fd) : fd(fd) {}
    UnixSocket::UnixSocket(unsigned int fd) : UnixSocket((int)fd) {}
    UnixSocket::UnixSocket(const UnixSocket &s) : UnixSocket(s.fd) {}
    UnixSocket::UnixSocket(UnixSocket &&s) : UnixSocket((unsigned int)s.fd) {
        s.fd = -1;
    }

    UnixSocket::~UnixSocket() {
        if(fd > -1) {
            ::close(fd);
        }
    }

    expected<UnixSocket, std::string> UnixSocket::accept() {
        /******************************************/
        /* Accept an incoming connection          */
        /******************************************/
        int clientfd = ::accept(fd, NULL, NULL);
        if(clientfd < 0) {
            ::close(clientfd);
            return unexpected<std::string>(std::string("Failed to accept client connection"));
        } else {
            return UnixSocket(clientfd);
        }
    }

    expected<void, std::string> UnixSocket::bind(std::string path) {
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

        if(::bind(fd, (struct sockaddr *) &(addr), sizeof(addr)) < 0) {
            return unexpected<std::string>(std::string("Failed to bind socket"));
        }

        return {};
    }

    expected<void, std::string> UnixSocket::listen(size_t maxConnections) {
        /******************************************/
        /* Listen for any client sockets          */
        /******************************************/

        if(::listen(fd, maxConnections) < 0) {
            return unexpected<std::string>(std::string("Failed to listen"));
        }

        return {};
    }

    expected<UnixSocket, std::string> UnixSocket::makeUnixSocket() {
        int fd = socket(AF_UNIX, SOCK_STREAM, 0);
        if(fd < 0) {
            ::close(fd);
            return unexpected<std::string>(std::string("Failed to create socket"));
        } else {
            return UnixSocket(fd);
        }
    }

    expected<std::string, std::string> UnixSocket::readLine(size_t maxBytes) {
        return readUntil('\n', maxBytes);
    }

    expected<std::string, std::string> UnixSocket::readUntil(char delimiter, size_t maxBytes) {
        char buffer[maxBytes];
        int recvCount = recvUntil(fd, buffer, delimiter, maxBytes);
        if(recvCount < 0) {
            return unexpected<std::string>(std::string("Failed to read delimited line from socket"));
        } else if(recvCount == 0) {
            return unexpected<std::string>(std::string("Ignoring empty message from socket"));
        }
        return std::string(buffer);
    }

    expected<void, std::string> UnixSocket::write(std::string message) {
        if(send(fd, message.data(), message.size(), MSG_NOSIGNAL) < 0) {
            return unexpected<std::string>(std::string("Failed to send message to client"));
        }

        return {};
    }
}
