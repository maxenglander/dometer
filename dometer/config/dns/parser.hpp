#pragma once

#include "dometer/app/dns/options.hpp"
#include "dometer/config/dns/resolver/parser.hpp"
#include "dometer/config/dns/server/parser.hpp"
#include "json/json.h"

namespace app = dometer::app;

namespace dometer::config::dns {
    class parser {
        public:
            parser();
            parser(dometer::config::dns::resolver::parser,
                   dometer::config::dns::server::parser);
            app::dns::options fromJson(const Json::Value& jsonValue) const;
        private:
            const dometer::config::dns::resolver::parser resolverParser;
            const dometer::config::dns::server::parser serverParser;
    };
}
