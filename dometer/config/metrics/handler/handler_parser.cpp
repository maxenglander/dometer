#include <cassert>

#include "dometer/config/metrics/handler/handler_parser.hpp"
#include "dometer/metrics/handler/options.hpp"
#include "json/json.h"

namespace dometer::config::metrics::handler {
    HandlerParser::HandlerParser()
        : HandlerParser::HandlerParser(dometer::config::metrics::handler::PrometheusHandlerParser()) {}

    HandlerParser::HandlerParser(dometer::config::metrics::handler::PrometheusHandlerParser prometheusParser)
        : prometheusParser(prometheusParser) {}

    dometer::metrics::handler::Options HandlerParser::fromJson(const Json::Value& jsonValue) const {
        assert(jsonValue.isMember("type"));
        assert(jsonValue["type"].isString());
        std::string type = jsonValue["type"].asString();
        
        if(type == "prometheus") {
            assert(jsonValue.isMember("prometheus"));
            assert(jsonValue["prometheus"].isObject());

            return prometheusParser.fromJson(jsonValue["prometheus"]);
        } else {
            assert(false);
        }
    }
}
