#pragma once

#include <string>

#include "json/json.h"
#include "std/experimental/expected.h"
#include "util/json_serde.h"

using namespace DnsTelemeter::Util;
using namespace std::experimental;

namespace DnsTelemeter::PowerDns {
    class UnixSocketRemoteBackend {
        public:
            UnixSocketRemoteBackend()
                : UnixSocketRemoteBackend(JsonSerde(), 100, 4096, "/var/run/dns-telemeter.sock") {};
            UnixSocketRemoteBackend(
                    JsonSerde jsonSerde,
                    unsigned int maxConnections,
                    unsigned int maxMessageSize,
                    std::string socketPath);
            expected<void, std::string> serve();
        private:
            JsonSerde jsonSerde;
            unsigned int maxConnections;
            unsigned int maxMessageSize;
            std::string socketPath;
    };
}
