#pragma once

#include "dometer/config/dns/resolver/libresolv_parser.hpp"
#include "dometer/dns/resolver/options.hpp"
#include "json/json.h"

namespace dometer::config::dns::resolver {
    class parser {
        public:
            parser();
            parser(LibresolvParser);
            dometer::dns::resolver::options fromJson(const Json::Value& jsonValue) const;
        private:
            const LibresolvParser libresolvParser;
    };
}
