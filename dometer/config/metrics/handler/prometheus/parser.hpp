#pragma once

#include "dometer/config/metrics/handler/prometheus/transport_parser.hpp"
#include "dometer/metrics/handler/prometheus/options.hpp"
#include "json/json.h"

namespace dometer::config::metrics::handler::prometheus {
    class parser {
        public:
            parser();
            parser(TransportParser);
            dometer::metrics::handler::prometheus::options fromJson(const Json::Value& jsonValue) const;
        private:
            dometer::config::metrics::handler::prometheus::TransportParser transportParser;
    };
}
