#pragma once

#include "dometer/config/metrics/handler/prometheus/pull_transport_parser.hpp"
#include "dometer/metrics/handler/prometheus/transport_options.hpp"
#include "json/json.h"

namespace dometer::config::metrics::handler::prometheus {
    class transport_parser {
        public:
            transport_parser();
            transport_parser(dometer::config::metrics::handler::prometheus::pull_transport_parser);
            dometer::metrics::handler::prometheus::transport_options from_json(const Json::Value&) const;
        private:
            dometer::config::metrics::handler::prometheus::pull_transport_parser pull_transport_parser;
    };
}
