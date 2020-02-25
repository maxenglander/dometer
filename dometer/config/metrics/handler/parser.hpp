#pragma once

#include "dometer/config/metrics/handler/prometheus_handler_parser.hpp"
#include "dometer/metrics/handler/options.hpp"
#include "json/json.h"

namespace dometer::config::metrics::handler {
    class Parser {
        public:
            Parser();
            Parser(dometer::config::metrics::handler::PrometheusHandlerParser);
            dometer::metrics::handler::Options fromJson(const Json::Value& jsonValue) const;
        private:
            dometer::config::metrics::handler::PrometheusHandlerParser prometheusParser;
    };
}
