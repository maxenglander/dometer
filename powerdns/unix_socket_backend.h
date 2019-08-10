#include <string>

#include "std/experimental/expected.h"

using namespace std::experimental;

namespace DnsTelemeter::PowerDns {
    class UnixSocketBackend {
        public:
            UnixSocketBackend(std::string path, unsigned int maxConnections);
            expected<void, std::string> serve();
        private:
            std::string makeSocketError(std::string description);
            std::string socketPath;
            unsigned int maxConnections;
    };
}
