#include <vector>

#include "dometer/config/metrics/handler/handler_parser.hpp"
#include "dometer/config/metrics/metrics_parser.hpp"
#include "dometer/metrics/options.hpp"
#include "dometer/metrics/handler/options.hpp"
#include "rapidjson/document.h"

namespace dometer::config::metrics {
    MetricsParser::MetricsParser()
        : MetricsParser::MetricsParser(dometer::config::metrics::handler::HandlerParser()) {}

    MetricsParser::MetricsParser(dometer::config::metrics::handler::HandlerParser handlerParser)
        : handlerParser(handlerParser) {}

    dometer::metrics::Options MetricsParser::fromJson(const rapidjson::Value& jsonValue) const {
        assert(jsonValue.HasMember("handlers"));
        assert(jsonValue["handlers"].IsArray());

        std::vector<dometer::metrics::handler::Options> handlers;
        for(rapidjson::SizeType i = 0; i < jsonValue["handlers"].Size(); i++) {
            handlers.push_back(handlerParser.fromJson(jsonValue["handlers"][i]));
        }

        return dometer::metrics::Options{
            handlers
        };
    }
}
