#pragma once

#include "config/dns/resolver/libresolv.hpp"
#include "rapidjson/document.h"

namespace dometer::config::dns::resolver {
    class LibresolvFactory {
        public:
            Libresolv fromJson(const rapidjson::Value& jsonValue) const;
    };
}
