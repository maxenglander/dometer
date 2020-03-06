#include <cassert>

#include "dometer/app/dns/options.hpp"
#include "dometer/config/dns/parser.hpp"
#include "dometer/config/dns/resolver/parser.hpp"
#include "dometer/config/dns/server/parser.hpp"
#include "json/json.h"

namespace app = dometer::app;

namespace dometer::config::dns {
    parser::parser()
        : parser::parser(dometer::config::dns::resolver::parser(),
                                 dometer::config::dns::server::parser()) {}

    parser::parser(dometer::config::dns::resolver::parser resolverParser,
                           dometer::config::dns::server::parser serverParser)
        : resolverParser(resolverParser), serverParser(serverParser) {}

    app::dns::options parser::fromJson(const Json::Value& jsonValue) const {
        assert(jsonValue.isMember("resolver"));
        assert(jsonValue["resolver"].isObject());
        assert(jsonValue.isMember("server"));
        assert(jsonValue["server"].isObject());

        return app::dns::options{
            resolverParser.fromJson(jsonValue["resolver"]),
            serverParser.fromJson(jsonValue["server"])
        };
    }
}
