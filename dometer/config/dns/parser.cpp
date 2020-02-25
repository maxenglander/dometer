#include <cassert>

#include "dometer/app/dns/options.hpp"
#include "dometer/config/dns/parser.hpp"
#include "dometer/config/dns/resolver/parser.hpp"
#include "dometer/config/dns/server/parser.hpp"
#include "json/json.h"

namespace app = dometer::app;

namespace dometer::config::dns {
    Parser::Parser()
        : Parser::Parser(dometer::config::dns::resolver::Parser(),
                                 dometer::config::dns::server::Parser()) {}

    Parser::Parser(dometer::config::dns::resolver::Parser resolverParser,
                           dometer::config::dns::server::Parser serverParser)
        : resolverParser(resolverParser), serverParser(serverParser) {}

    app::dns::Options Parser::fromJson(const Json::Value& jsonValue) const {
        assert(jsonValue.isMember("resolver"));
        assert(jsonValue["resolver"].isObject());
        assert(jsonValue.isMember("server"));
        assert(jsonValue["server"].isObject());

        return app::dns::Options{
            resolverParser.fromJson(jsonValue["resolver"]),
            serverParser.fromJson(jsonValue["server"])
        };
    }
}
