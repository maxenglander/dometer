#pragma once

#include "dometer/config/metrics/handler/prometheus/transport_parser.hpp"
#include "dometer/metrics/handler/prometheus/options.hpp"
#include "json/json.h"

namespace dometer::config::metrics::handler::prometheus {
    class parser {
        public:
            parser();
            parser(transport_parser);
            dometer::metrics::handler::prometheus::options from_json(const Json::Value&) const;
        private:
            dometer::config::metrics::handler::prometheus::transport_parser _transport_parser;
    };
}
