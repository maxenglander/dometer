#pragma once

#include "dometer/config/dns/resolver/libresolv_parser.hpp"
#include "dometer/dns/resolver/options.hpp"
#include "json/json.h"

namespace dometer::config::dns::resolver {
    class Parser {
        public:
            Parser();
            Parser(LibresolvParser);
            dometer::dns::resolver::Options fromJson(const Json::Value& jsonValue) const;
        private:
            const LibresolvParser libresolvParser;
    };
}
