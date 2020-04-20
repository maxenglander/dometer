#include <cassert>

#include "dometer/config/dns/resolver/libresolv_parser.hpp"
#include "dometer/dns/resolver/libresolv_function.hpp"
#include "dometer/dns/resolver/libresolv_options.hpp"
#include "json/json.h"

namespace dometer::config::dns::resolver {
    dometer::dns::resolver::libresolv_options libresolv_parser::from_json(const Json::Value& json_value) const {
        assert(json_value.isMember("function"));
        assert(json_value["function"].isString());

        return dometer::dns::resolver::libresolv_options{
        };
    }
}
