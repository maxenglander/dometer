#pragma once

#include "dometer/app/metrics/options.hpp"
#include "dometer/config/metrics/handler/parser.hpp"
#include "json/json.h"

namespace app = dometer::app;

namespace dometer::config::metrics {
    class Parser {
        public:
            Parser();
            Parser(dometer::config::metrics::handler::Parser);
            app::metrics::Options fromJson(const Json::Value& jsonValue) const;
        private:
            const dometer::config::metrics::handler::Parser handlerParser;
    };
}
