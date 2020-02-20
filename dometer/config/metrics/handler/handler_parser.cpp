#include "dometer/config/metrics/handler/handler_parser.hpp"
#include "dometer/metrics/handler/options.hpp"
#include "rapidjson/document.h"

namespace dometer::config::metrics::handler {
    HandlerParser::HandlerParser()
        : HandlerParser::HandlerParser(dometer::config::metrics::handler::PrometheusHandlerParser()) {}

    HandlerParser::HandlerParser(dometer::config::metrics::handler::PrometheusHandlerParser prometheusParser)
        : prometheusParser(prometheusParser) {}

    dometer::metrics::handler::Options HandlerParser::fromJson(const rapidjson::Value& jsonValue) const {
        assert(jsonValue.HasMember("type"));
        assert(jsonValue["type"].IsString());
        std::string type = jsonValue["type"].GetString();
        
        if(type == "prometheus") {
            assert(jsonValue.HasMember("prometheus"));
            assert(jsonValue["prometheus"].IsObject());

            return prometheusParser.fromJson(jsonValue["prometheus"]);
        } else {
            assert(false);
        }
    }
}
