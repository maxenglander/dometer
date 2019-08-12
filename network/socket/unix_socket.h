#pragma once

#include <string>

#include "std/experimental/expected.h"

using namespace std::experimental;

namespace DnsTelemeter::Network {
    class UnixSocket {
        public:
            UnixSocket();
            expected<std::unique_ptr<UnixSocket>, std::string> accept();
            expected<void, std::string> close();
            expected<void, std::string> bind(std::string address);
            expected<void, std::string> listen(unsigned int maxConnections);
        private:
            int fd;
    };
}
