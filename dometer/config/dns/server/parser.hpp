#pragma once

#include "dometer/dns/server/options.hpp"
#include "dometer/config/dns/server/transport_parser.hpp"
#include "json/json.h"

namespace dometer::config::dns::server {
    class parser {
        public:
            parser();
            parser(TransportParser);
            dometer::dns::server::options fromJson(const Json::Value& jsonValue) const;
        private:
            const TransportParser transportParser;
    };
}
