#pragma once

#include "dometer/config/dns/resolver/libresolv_parser.hpp"
#include "dometer/dns/resolver/options.hpp"
#include "rapidjson/document.h"

namespace dometer::config::dns::resolver {
    class ResolverParser {
        public:
            ResolverParser();
            ResolverParser(LibresolvParser);
            dometer::dns::resolver::Options fromJson(const rapidjson::Value& jsonValue) const;
        private:
            const LibresolvParser libresolvParser;
    };
}
