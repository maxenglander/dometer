#pragma once

#include "json/json.h"

namespace DnsTelemeter::PowerDns {
    class RemoteBackendReplies {
        public:
            static Json::Value failure();
    };
}
