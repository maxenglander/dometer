#pragma once

#include "config/metrics/handler/handler_parser.hpp"
#include "metrics/options.hpp"
#include "rapidjson/document.h"

namespace dometer::config::metrics {
    class MetricsParser {
        public:
            MetricsParser();
            MetricsParser(dometer::config::metrics::handler::HandlerParser);
            dometer::metrics::Options fromJson(const rapidjson::Value& jsonValue) const;
        private:
            const dometer::config::metrics::handler::HandlerParser handlerParser;
    };
}
