#pragma once

#include "dometer/app/metrics/options.hpp"
#include "dometer/config/metrics/handler/handler_parser.hpp"
#include "json/json.h"

namespace app = dometer::app;

namespace dometer::config::metrics {
    class MetricsParser {
        public:
            MetricsParser();
            MetricsParser(dometer::config::metrics::handler::HandlerParser);
            app::metrics::Options fromJson(const Json::Value& jsonValue) const;
        private:
            const dometer::config::metrics::handler::HandlerParser handlerParser;
    };
}
