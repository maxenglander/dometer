#pragma once

#include "dometer/dns/server/options.hpp"
#include "dometer/config/dns/server/transport_parser.hpp"
#include "json/json.h"

namespace dometer::config::dns::server {
    class ServerParser {
        public:
            ServerParser();
            ServerParser(TransportParser);
            dometer::dns::server::Options fromJson(const Json::Value& jsonValue) const;
        private:
            const TransportParser transportParser;
    };
}
