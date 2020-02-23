#pragma once

#include "json/json.h"

namespace dometer::config::dns::server {
    class TransportParser {
        public:
            Transport fromJson(const Json::Value& jsonValue) const;
    };
}
