#pragma once

#include "dometer/config/metrics/handler/parser.hpp"
#include "dometer/metrics/options.hpp"
#include "json/json.h"

namespace dometer::config::metrics {
    class parser {
        public:
            parser();
            parser(dometer::config::metrics::handler::parser);
            dometer::metrics::options from_json(const Json::Value&) const;
        private:
            const dometer::config::metrics::handler::parser handler_parser;
    };
}
