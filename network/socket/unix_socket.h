#pragma once

#include <string>

#include "std/experimental/expected.h"

using namespace std::experimental;

namespace DnsTelemeter::Network::Socket {
    class UnixSocket {
        public:
            UnixSocket(unsigned int fd);
            expected<UnixSocket, std::string> accept();
            expected<void, std::string> close();
            expected<void, std::string> bind(std::string address);
            expected<void, std::string> listen(unsigned int maxConnections);
            static expected<UnixSocket, std::string> makeUnixSocket();
        private:
            unsigned int fd;
    };
}
