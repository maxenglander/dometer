#include "dometer/config/dns/resolver/libresolv_parser.hpp"
#include "dometer/dns/resolver/libresolv_function.hpp"
#include "dometer/dns/resolver/libresolv_options.hpp"
#include "rapidjson/document.h"

namespace dometer::config::dns::resolver {
    dometer::dns::resolver::LibresolvOptions LibresolvParser::fromJson(const rapidjson::Value& jsonValue) const {
        assert(jsonValue.HasMember("function"));
        assert(jsonValue["function"].IsString());

        return dometer::dns::resolver::LibresolvOptions{
        };
    }
}
