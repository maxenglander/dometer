#pragma once

#include <string>

#include "std/experimental/expected.h"

using namespace std::experimental;

namespace DnsTelemeter::Network::Socket {
    class UnixSocket {
        public:
            ~UnixSocket();
            expected<UnixSocket, std::string> accept();
            expected<void, std::string> close();
            expected<void, std::string> bind(std::string address);
            expected<void, std::string> listen(size_t maxConnections);
            static expected<UnixSocket, std::string> makeUnixSocket();
            expected<std::string, std::string> readUntil(char delimiter, size_t maxBytes);
        private:
            UnixSocket(unsigned int fd);
            unsigned int fd;
    };
}
