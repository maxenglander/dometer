#include <cassert>
#include <string>

#include "dometer/config/dns/resolver/libresolv_parser.hpp"
#include "dometer/config/dns/resolver/parser.hpp"
#include "dometer/dns/resolver/options.hpp"
#include "std/x/optional.hpp"
#include "json/json.h"

namespace dometer::config::dns::resolver {
    Parser::Parser() : Parser::Parser(LibresolvParser()) {}

    Parser::Parser(LibresolvParser libresolvParser)
        : libresolvParser(libresolvParser) {}

    dometer::dns::resolver::Options Parser::fromJson(const Json::Value& jsonValue) const {
        assert(jsonValue.isMember("type"));
        assert(jsonValue["type"].isString());
        std::string type = jsonValue["type"].asString();

        if(type == "libresolv") {
            assert(jsonValue.isMember("libresolv"));
            assert(jsonValue["libresolv"].isObject());
            return libresolvParser.fromJson(jsonValue["libresolv"]);
        }

        assert(false);
    }
}
