#pragma once

#include "dometer/config/metrics/handler/prometheus/pull_transport_parser.hpp"
#include "dometer/metrics/handler/prometheus/transport_options.hpp"
#include "json/json.h"

namespace dometer::config::metrics::handler::prometheus {
    class TransportParser {
        public:
            TransportParser();
            TransportParser(dometer::config::metrics::handler::prometheus::PullTransportParser);
            dometer::metrics::handler::prometheus::TransportOptions fromJson(const Json::Value& jsonValue) const;
        private:
            dometer::config::metrics::handler::prometheus::PullTransportParser pullTransportParser;
    };
}
