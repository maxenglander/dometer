#pragma once

#include <string>

#include "json/json.h"
#include "powerdns/remote_backend_router.h"
#include "std/experimental/expected.h"
#include "util/json_serde.h"

using namespace Dometer::Util;
using namespace std::experimental;

namespace Dometer::PowerDns {
    class UnixSocketRemoteBackend {
        public:
            UnixSocketRemoteBackend(
                    JsonSerde jsonSerde,
                    unsigned int maxConnections,
                    unsigned int maxMessageSize,
                    RemoteBackendRouter router,
                    std::string socketPath);
            expected<void, std::string> serve();
        private:
            JsonSerde jsonSerde;
            unsigned int maxConnections;
            unsigned int maxMessageSize;
            RemoteBackendRouter router;
            std::string socketPath;
    };
}
