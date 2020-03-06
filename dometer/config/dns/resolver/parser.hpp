#pragma once

#include "dometer/config/dns/resolver/libresolv_parser.hpp"
#include "dometer/dns/resolver/options.hpp"
#include "json/json.h"

namespace dometer::config::dns::resolver {
    class parser {
        public:
            parser();
            parser(libresolv_parser);
            dometer::dns::resolver::options fromJson(const Json::Value&) const;
        private:
            const libresolv_parser _libresolv_parser;
    };
}
