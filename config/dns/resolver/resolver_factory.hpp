#pragma once

#include "config/dns/resolver/libresolv_factory.hpp"
#include "config/dns/resolver/resolver_factory.hpp"
#include "rapidjson/document.h"

namespace dometer::config::dns::resolver {
    class ResolverFactory {
        public:
            ResolverFactory();
            ResolverFactory(LibresolvFactory);
            Resolver fromJson(const rapidjson::Value& jsonValue) const;
        private:
            const LibresolvFactory libresolvFactory;
    };
}