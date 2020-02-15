#pragma once

#include "config/dns/resolver/libresolv_factory.hpp"
#include "dns/resolver/options.hpp"
#include "rapidjson/document.h"

namespace dometer::config::dns::resolver {
    class ResolverFactory {
        public:
            ResolverFactory();
            ResolverFactory(LibresolvFactory);
            dometer::dns::resolver::Options fromJson(const rapidjson::Value& jsonValue) const;
        private:
            const LibresolvFactory libresolvFactory;
    };
}
