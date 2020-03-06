#include <cassert>
#include <string>

#include "dometer/config/dns/resolver/libresolv_parser.hpp"
#include "dometer/config/dns/resolver/parser.hpp"
#include "dometer/dns/resolver/options.hpp"
#include "std/x/optional.hpp"
#include "json/json.h"

namespace dometer::config::dns::resolver {
    parser::parser() : parser::parser(libresolv_parser()) {}

    parser::parser(libresolv_parser _libresolv_parser)
        : _libresolv_parser(_libresolv_parser) {}

    dometer::dns::resolver::options parser::from_json(const Json::Value& json_value) const {
        assert(json_value.isMember("type"));
        assert(json_value["type"].isString());
        std::string type = json_value["type"].asString();

        if(type == "libresolv") {
            assert(json_value.isMember("libresolv"));
            assert(json_value["libresolv"].isObject());
            return _libresolv_parser.from_json(json_value["libresolv"]);
        }

        assert(false);
    }
}
