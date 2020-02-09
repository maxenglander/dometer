#pragma once

#include "rapidjson/document.h"

namespace dometer::config::dns::server {
    class TransportFactory {
        public:
            Transport fromJson(const rapidjson::Value& jsonValue) const;
    };
}
