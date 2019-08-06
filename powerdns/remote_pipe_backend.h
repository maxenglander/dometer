#include <string>

namespace DnsTelemeter::PowerDns {
    class RemotePipeBackend {
        public:
            RemotePipeBackend(std::string path);
            void run();
        private:
            std::string path;
    };
}
