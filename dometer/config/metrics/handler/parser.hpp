#pragma once

#include "dometer/config/metrics/handler/prometheus/parser.hpp"
#include "dometer/metrics/handler/options.hpp"
#include "json/json.h"

namespace dometer::config::metrics::handler {
    class parser {
        public:
            parser();
            parser(dometer::config::metrics::handler::prometheus::parser);
            dometer::metrics::handler::options from_json(const Json::Value&) const;
        private:
            dometer::config::metrics::handler::prometheus::parser prometheus_parser;
    };
}
