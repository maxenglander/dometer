#pragma once

#include "rapidjson/document.h"

namespace dometer::config::dns::server {
    class TransportParser {
        public:
            Transport fromJson(const rapidjson::Value& jsonValue) const;
    };
}
