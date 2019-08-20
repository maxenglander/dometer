#pragma once

#include <string>
#include <unordered_map>

#include "json/json.h"
#include "powerdns/remote_backend_handler.h"
#include "std/experimental/expected.h"

using namespace std::experimental;

namespace DnsTelemeter::PowerDns {
    class RemoteBackendRouter {
        public:
            RemoteBackendRouter();
            void on(std::string method, RemoteBackendHandler handler);
            Json::Value route(Json::Value query);
        private:
            std::unordered_map<std::string, RemoteBackendHandler> handlers;
    };
}
