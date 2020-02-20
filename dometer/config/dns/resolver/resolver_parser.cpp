#include <string>

#include "dometer/config/dns/resolver/libresolv_parser.hpp"
#include "dometer/config/dns/resolver/resolver_parser.hpp"
#include "dometer/dns/resolver/options.hpp"
#include "std/x/optional.hpp"
#include "rapidjson/document.h"

namespace dometer::config::dns::resolver {
    ResolverParser::ResolverParser() : ResolverParser::ResolverParser(LibresolvParser()) {}

    ResolverParser::ResolverParser(LibresolvParser libresolvParser)
        : libresolvParser(libresolvParser) {}

    dometer::dns::resolver::Options ResolverParser::fromJson(const rapidjson::Value& jsonValue) const {
        assert(jsonValue.HasMember("type"));
        assert(jsonValue["type"].IsString());
        std::string type = jsonValue["type"].GetString();

        if(type == "libresolv") {
            assert(jsonValue.HasMember("libresolv"));
            assert(jsonValue["libresolv"].IsObject());
            return libresolvParser.fromJson(jsonValue["libresolv"]);
        }

        assert(false);
    }
}
