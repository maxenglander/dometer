#pragma once

#include "dometer/app/metrics/options.hpp"
#include "dometer/config/metrics/handler/parser.hpp"
#include "json/json.h"

namespace app = dometer::app;

namespace dometer::config::metrics {
    class parser {
        public:
            parser();
            parser(dometer::config::metrics::handler::parser);
            app::metrics::options fromJson(const Json::Value& jsonValue) const;
        private:
            const dometer::config::metrics::handler::parser handlerParser;
    };
}
