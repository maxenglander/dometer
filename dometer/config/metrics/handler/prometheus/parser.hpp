#pragma once

#include "dometer/config/metrics/handler/prometheus/transport_parser.hpp"
#include "dometer/metrics/handler/prometheus/options.hpp"
#include "json/json.h"

namespace dometer::config::metrics::handler::prometheus {
    class Parser {
        public:
            Parser();
            Parser(TransportParser);
            dometer::metrics::handler::prometheus::Options fromJson(const Json::Value& jsonValue) const;
        private:
            dometer::config::metrics::handler::prometheus::TransportParser transportParser;
    };
}
