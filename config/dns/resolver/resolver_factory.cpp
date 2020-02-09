#include <string>

#include "config/dns/resolver/libresolv_factory.hpp"
#include "config/dns/resolver/resolver.hpp"
#include "config/dns/resolver/resolver_factory.hpp"
#include "x/optional.hpp"
#include "rapidjson/document.h"

namespace dometer::config::dns::resolver {
    ResolverFactory::ResolverFactory() : ResolverFactory::ResolverFactory(LibresolvFactory()) {}

    ResolverFactory::ResolverFactory(LibresolvFactory libresolvFactory)
        : libresolvFactory(libresolvFactory) {}

    Resolver ResolverFactory::fromJson(const rapidjson::Value& jsonValue) const {
        assert(jsonValue.HasMember("type"));
        assert(jsonValue["type"].IsString());
        std::string type = jsonValue["type"].GetString();

        if(type == "libresolv") {
            assert(jsonValue.HasMember("libresolv"));
            assert(jsonValue["libresolv"].IsObject());
            return Resolver{
                type,
                libresolvFactory.fromJson(jsonValue["libresolv"])
            };
        } else {
            return Resolver{
                type,
                {}
            };
        }
    }
}
