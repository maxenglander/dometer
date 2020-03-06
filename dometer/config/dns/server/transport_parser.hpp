#pragma once

#include "dometer/dns/server/transport_options.hpp"
#include "json/json.h"

namespace dometer::config::dns::server {
    class transport_parser {
        public:
            dometer::dns::server::transport_options fromJson(const Json::Value&) const;
    };
}
