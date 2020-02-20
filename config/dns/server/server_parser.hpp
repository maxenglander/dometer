#pragma once

#include "config/dns/server/server.hpp"
#include "config/dns/server/transport_parser.hpp"
#include "rapidjson/document.h"

namespace dometer::config::dns::server {
    class ServerParser {
        public:
            ServerParser();
            ServerParser(TransportParser);
            Server fromJson(const rapidjson::Value& jsonValue) const;
        private:
            const TransportParser transportParser;
    };
}
