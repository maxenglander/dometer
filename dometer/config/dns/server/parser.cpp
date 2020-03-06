#include <cassert>

#include "dometer/dns/server/options.hpp"
#include "dometer/dns/server/transport_options.hpp"
#include "dometer/config/dns/server/parser.hpp"
#include "dometer/config/dns/server/transport_parser.hpp"
#include "json/json.h"

namespace dometer::config::dns::server {
    parser::parser() : parser::parser(transport_parser()) {}
    parser::parser(transport_parser transport_parser_) : transport_parser_(transport_parser_) {}

    dometer::dns::server::options parser::from_json(const Json::Value& json_value) const {
        assert(json_value.isMember("transport"));
        assert(json_value["transport"].isObject());
        return dometer::dns::server::options{
            transport_parser_.from_json(json_value["transport"])
        };
    }
}
