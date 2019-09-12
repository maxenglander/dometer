#pragma once

#include <string>
#include <sys/un.h>

#include "std/experimental/expected.hpp"

using namespace std::experimental;

namespace Dometer::Network::Socket {
    class UnixSocket {
        public:
            UnixSocket(const UnixSocket&);
            UnixSocket(UnixSocket&&);
            ~UnixSocket();

            expected<UnixSocket, std::string> accept();
            expected<void, std::string> close();
            expected<void, std::string> bind(std::string address);
            expected<void, std::string> listen(size_t maxConnections);
            static expected<UnixSocket, std::string> makeUnixSocket();
            expected<std::string, std::string> readLine(size_t maxBytes);
            expected<std::string, std::string> readUntil(char delimiter, size_t maxBytes);
            expected<void, std::string> write(std::string message);
        private:
            UnixSocket(unsigned int fd);
            UnixSocket(int fd);
            struct sockaddr_un addr;
            int fd;
    };
}
