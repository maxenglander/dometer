#pragma once

#include "dometer/config/metrics/handler/prometheus_pull_transport_parser.hpp"
#include "dometer/metrics/handler/prometheus_transport_options.hpp"
#include "rapidjson/document.h"

namespace dometer::config::metrics::handler {
    class PrometheusTransportParser {
        public:
            PrometheusTransportParser();
            PrometheusTransportParser(dometer::config::metrics::handler::PrometheusPullTransportParser);
            dometer::metrics::handler::PrometheusTransportOptions fromJson(const rapidjson::Value& jsonValue) const;
        private:
            dometer::config::metrics::handler::PrometheusPullTransportParser pullTransportParser;
    };
}
