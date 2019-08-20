#pragma once

#include "json/json.h"

namespace DnsTelemeter::PowerDns {
    class RemoteBackendHandler {
        public:
            virtual Json::Value handle(Json::Value);
    };
}
