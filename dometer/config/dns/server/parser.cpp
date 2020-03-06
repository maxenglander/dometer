#include <cassert>

#include "dometer/dns/server/options.hpp"
#include "dometer/dns/server/transport_options.hpp"
#include "dometer/config/dns/server/parser.hpp"
#include "dometer/config/dns/server/transport_parser.hpp"
#include "json/json.h"

namespace dometer::config::dns::server {
    parser::parser() : parser::parser(TransportParser()) {}
    parser::parser(TransportParser transportParser) : transportParser(transportParser) {}

    dometer::dns::server::options parser::fromJson(const Json::Value& jsonValue) const {
        assert(jsonValue.isMember("transport"));
        assert(jsonValue["transport"].isObject());
        return dometer::dns::server::options{
            transportParser.fromJson(jsonValue["transport"])
        };
    }
}
