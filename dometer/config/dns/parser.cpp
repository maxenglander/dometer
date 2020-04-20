#include <cassert>

#include "dometer/config/dns/parser.hpp"
#include "dometer/config/dns/resolver/parser.hpp"
#include "dometer/config/dns/server/parser.hpp"
#include "dometer/dns/options.hpp"
#include "json/json.h"

namespace dometer::config::dns {
    parser::parser()
        : parser::parser(dometer::config::dns::resolver::parser(),
                                 dometer::config::dns::server::parser()) {}

    parser::parser(dometer::config::dns::resolver::parser resolver_parser,
                           dometer::config::dns::server::parser server_parser)
        : resolver_parser(resolver_parser), server_parser(server_parser) {}

    dometer::dns::options parser::from_json(const Json::Value& json_value) const {
        assert(json_value.isMember("resolver"));
        assert(json_value["resolver"].isObject());
        assert(json_value.isMember("server"));
        assert(json_value["server"].isObject());

        return dometer::dns::options{
            resolver_parser.from_json(json_value["resolver"]),
            server_parser.from_json(json_value["server"])
        };
    }
}
