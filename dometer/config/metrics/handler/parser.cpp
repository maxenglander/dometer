#include <cassert>

#include "dometer/config/metrics/handler/parser.hpp"
#include "dometer/metrics/handler/options.hpp"
#include "json/json.h"

namespace dometer::config::metrics::handler {
    Parser::Parser()
        : Parser::Parser(dometer::config::metrics::handler::PrometheusHandlerParser()) {}

    Parser::Parser(dometer::config::metrics::handler::PrometheusHandlerParser prometheusParser)
        : prometheusParser(prometheusParser) {}

    dometer::metrics::handler::Options Parser::fromJson(const Json::Value& jsonValue) const {
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
