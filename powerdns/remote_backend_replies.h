#pragma once

#include "json/json.h"

namespace Dometer::PowerDns {
    class RemoteBackendReplies {
        public:
            static Json::Value failure();
            static Json::Value success();
    };
}
