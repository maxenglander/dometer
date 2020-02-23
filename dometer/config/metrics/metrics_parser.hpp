#pragma once

#include "dometer/config/metrics/handler/handler_parser.hpp"
#include "dometer/metrics/options.hpp"
#include "json/json.h"

namespace dometer::config::metrics {
    class MetricsParser {
        public:
            MetricsParser();
            MetricsParser(dometer::config::metrics::handler::HandlerParser);
            dometer::metrics::Options fromJson(const Json::Value& jsonValue) const;
        private:
            const dometer::config::metrics::handler::HandlerParser handlerParser;
    };
}
