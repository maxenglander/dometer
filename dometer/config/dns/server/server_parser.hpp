#pragma once

#include "dometer/config/dns/server/server.hpp"
#include "dometer/config/dns/server/transport_parser.hpp"
#include "json/json.h"

namespace dometer::config::dns::server {
    class ServerParser {
        public:
            ServerParser();
            ServerParser(TransportParser);
            Server fromJson(const Json::Value& jsonValue) const;
        private:
            const TransportParser transportParser;
    };
}
