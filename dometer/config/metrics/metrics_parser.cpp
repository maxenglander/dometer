#include <cassert>
#include <vector>

#include "dometer/app/metrics/options.hpp"
#include "dometer/config/metrics/handler/handler_parser.hpp"
#include "dometer/config/metrics/metrics_parser.hpp"
#include "dometer/metrics/handler/options.hpp"
#include "json/json.h"

namespace app = dometer::app;

namespace dometer::config::metrics {
    MetricsParser::MetricsParser()
        : MetricsParser::MetricsParser(dometer::config::metrics::handler::HandlerParser()) {}

    MetricsParser::MetricsParser(dometer::config::metrics::handler::HandlerParser handlerParser)
        : handlerParser(handlerParser) {}

    dometer::app::metrics::Options MetricsParser::fromJson(const Json::Value& jsonValue) const {
        assert(jsonValue.isMember("handlers"));
        assert(jsonValue["handlers"].isArray());

        std::vector<dometer::metrics::handler::Options> handlers;
        for(Json::Value::ArrayIndex i = 0; i < jsonValue["handlers"].size(); i++) {
            handlers.push_back(handlerParser.fromJson(jsonValue["handlers"][i]));
        }

        return dometer::app::metrics::Options{
            handlers
        };
    }
}
