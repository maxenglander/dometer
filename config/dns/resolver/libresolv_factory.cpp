#include "config/dns/resolver/libresolv.hpp"
#include "config/dns/resolver/libresolv_factory.hpp"
#include "rapidjson/document.h"

namespace dometer::config::dns::resolver {
    Libresolv LibresolvFactory::fromJson(const rapidjson::Value& jsonValue) const {
        assert(jsonValue.HasMember("function"));
        assert(jsonValue["function"].IsString());
        return Libresolv {
            jsonValue["function"].GetString()
        };
    }
}
