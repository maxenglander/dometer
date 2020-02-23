#include <cassert>

#include "dometer/config/dns/resolver/libresolv_parser.hpp"
#include "dometer/dns/resolver/libresolv_function.hpp"
#include "dometer/dns/resolver/libresolv_options.hpp"
#include "json/json.h"

namespace dometer::config::dns::resolver {
    dometer::dns::resolver::LibresolvOptions LibresolvParser::fromJson(const Json::Value& jsonValue) const {
        assert(jsonValue.isMember("function"));
        assert(jsonValue["function"].isString());

        return dometer::dns::resolver::LibresolvOptions{
        };
    }
}
