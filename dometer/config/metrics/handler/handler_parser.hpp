#pragma once

#include "dometer/config/metrics/handler/prometheus_handler_parser.hpp"
#include "dometer/metrics/handler/options.hpp"
#include "rapidjson/document.h"

namespace dometer::config::metrics::handler {
    class HandlerParser {
        public:
            HandlerParser();
            HandlerParser(dometer::config::metrics::handler::PrometheusHandlerParser);
            dometer::metrics::handler::Options fromJson(const rapidjson::Value& jsonValue) const;
        private:
            dometer::config::metrics::handler::PrometheusHandlerParser prometheusParser;
    };
}
