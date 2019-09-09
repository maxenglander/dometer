#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "json/json.h"
#include "powerdns/remote_backend_handler.h"
#include "std/experimental/expected.h"

using namespace std::experimental;

namespace Dometer::PowerDns {
    class RemoteBackendRouter {
        public:
            RemoteBackendRouter();
            void on(std::string method, std::shared_ptr<RemoteBackendHandler> handler);
            Json::Value route(Json::Value query);
        private:
            std::unordered_map<std::string, std::shared_ptr<RemoteBackendHandler>> handlers;
    };
}
