#include <string>

#include "std/experimental/expected.h"

using namespace std::experimental;

namespace DnsTelemeter::PowerDns {
    class UnixSocketBackend {
        public:
            UnixSocketBackend() : UnixSocketBackend(100, 4096, "/var/run/dns-telemeter.sock") {};
            UnixSocketBackend(
                    unsigned int maxConnections,
                    unsigned int maxMessageSize,
                    std::string socketPath);
            expected<void, std::string> serve();
        private:
            std::string makeSocketError(std::string description);
            unsigned int maxConnections;
            unsigned int maxMessageSize;
            std::string socketPath;
    };
}
