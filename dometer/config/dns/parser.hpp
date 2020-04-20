#pragma once

#include "dometer/config/dns/resolver/parser.hpp"
#include "dometer/config/dns/server/parser.hpp"
#include "dometer/dns/options.hpp"
#include "json/json.h"

namespace dometer::config::dns {
    class parser {
        public:
            parser();
            parser(dometer::config::dns::resolver::parser,
                   dometer::config::dns::server::parser);
            dometer::dns::options from_json(const Json::Value&) const;
        private:
            const dometer::config::dns::resolver::parser resolver_parser;
            const dometer::config::dns::server::parser server_parser;
    };
}
