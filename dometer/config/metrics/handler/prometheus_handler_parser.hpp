#pragma once

#include "dometer/config/metrics/handler/prometheus_transport_parser.hpp"
#include "dometer/metrics/handler/prometheus_options.hpp"
#include "json/json.h"

namespace dometer::config::metrics::handler {
    class PrometheusHandlerParser {
        public:
            PrometheusHandlerParser();
            PrometheusHandlerParser(PrometheusTransportParser);
            dometer::metrics::handler::PrometheusOptions fromJson(const Json::Value& jsonValue) const;
        private:
            dometer::config::metrics::handler::PrometheusTransportParser transportParser;
    };
}
