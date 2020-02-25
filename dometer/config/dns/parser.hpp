#pragma once

#include "dometer/app/dns/options.hpp"
#include "dometer/config/dns/resolver/parser.hpp"
#include "dometer/config/dns/server/parser.hpp"
#include "json/json.h"

namespace app = dometer::app;

namespace dometer::config::dns {
    class Parser {
        public:
            Parser();
            Parser(dometer::config::dns::resolver::Parser,
                    dometer::config::dns::server::Parser);
            app::dns::Options fromJson(const Json::Value& jsonValue) const;
        private:
            const dometer::config::dns::resolver::Parser resolverParser;
            const dometer::config::dns::server::Parser serverParser;
    };
}
