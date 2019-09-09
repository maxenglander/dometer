#pragma once

#include "json/json.h"

namespace Dometer::PowerDns {
    class RemoteBackendHandler {
        public:
            virtual Json::Value handle(Json::Value) = 0;
    };
}
