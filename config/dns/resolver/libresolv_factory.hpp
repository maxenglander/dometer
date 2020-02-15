#pragma once

#include "dns/resolver/libresolv_options.hpp"
#include "rapidjson/document.h"

namespace dometer::config::dns::resolver {
    class LibresolvFactory {
        public:
            dometer::dns::resolver::LibresolvOptions fromJson(const rapidjson::Value& jsonValue) const;
    };
}
