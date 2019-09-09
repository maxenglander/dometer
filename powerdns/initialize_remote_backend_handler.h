#pragma once

#include <vector>

#include "json/json.h"
#include "powerdns/initialize_remote_backend_query.h"
#include "powerdns/remote_backend_handler.h"

namespace Dometer::PowerDns {
    class InitializeRemoteBackendHandler: public RemoteBackendHandler {
        public:
            virtual Json::Value handle(Json::Value query) override final;
            virtual bool handle(InitializeRemoteBackendQuery query) = 0;
        private:
            bool validate(Json::Value query);
    };
}
