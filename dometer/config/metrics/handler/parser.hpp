#pragma once

#include "dometer/config/metrics/handler/prometheus/parser.hpp"
#include "dometer/metrics/handler/options.hpp"
#include "json/json.h"

namespace dometer::config::metrics::handler {
    class Parser {
        public:
            Parser();
            Parser(dometer::config::metrics::handler::prometheus::Parser);
            dometer::metrics::handler::Options fromJson(const Json::Value& jsonValue) const;
        private:
            dometer::config::metrics::handler::prometheus::Parser prometheusParser;
    };
}
