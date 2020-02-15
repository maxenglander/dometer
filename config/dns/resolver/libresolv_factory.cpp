#include "config/dns/resolver/libresolv_factory.hpp"
#include "dns/resolver/libresolv_function.hpp"
#include "dns/resolver/libresolv_options.hpp"
#include "rapidjson/document.h"

namespace dometer::config::dns::resolver {
    dometer::dns::resolver::LibresolvOptions LibresolvFactory::fromJson(const rapidjson::Value& jsonValue) const {
        assert(jsonValue.HasMember("function"));
        assert(jsonValue["function"].IsString());

        return dometer::dns::resolver::LibresolvOptions{
        };
    }
}
