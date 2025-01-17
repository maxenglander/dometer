#pragma once

#include "dometer/dns/resolver/libresolv_options.hpp"
#include "json/json.h"

namespace dometer::config::dns::resolver {
    class libresolv_parser {
        public:
            dometer::dns::resolver::libresolv_options from_json(const Json::Value&) const;
    };
}
