#pragma once

#include "dometer/dns/server/transport_options.hpp"
#include "json/json.h"

namespace dometer::config::dns::server {
    class TransportParser {
        public:
            dometer::dns::server::TransportOptions fromJson(const Json::Value& jsonValue) const;
    };
}
