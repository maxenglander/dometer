#pragma once

#include "dometer/dns/resolver/libresolv_options.hpp"
#include "json/json.h"

namespace dometer::config::dns::resolver {
    class LibresolvParser {
        public:
            dometer::dns::resolver::LibresolvOptions fromJson(const Json::Value& jsonValue) const;
    };
}
