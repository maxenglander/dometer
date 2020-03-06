#pragma once

#include "dometer/dns/server/options.hpp"
#include "dometer/config/dns/server/transport_parser.hpp"
#include "json/json.h"

namespace dometer::config::dns::server {
    class parser {
        public:
            parser();
            parser(transport_parser);
            dometer::dns::server::options fromJson(const Json::Value&) const;
        private:
            const transport_parser transport_parser_;
    };
}
