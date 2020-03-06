#include <cassert>
#include <vector>

#include "dometer/app/metrics/options.hpp"
#include "dometer/config/metrics/handler/parser.hpp"
#include "dometer/config/metrics/parser.hpp"
#include "dometer/metrics/handler/options.hpp"
#include "json/json.h"

namespace app = dometer::app;

namespace dometer::config::metrics {
    parser::parser()
        : parser::parser(dometer::config::metrics::handler::parser()) {}

    parser::parser(dometer::config::metrics::handler::parser handlerParser)
        : handlerParser(handlerParser) {}

    dometer::app::metrics::options parser::fromJson(const Json::Value& jsonValue) const {
        assert(jsonValue.isMember("handlers"));
        assert(jsonValue["handlers"].isArray());

        std::vector<dometer::metrics::handler::options> handlers;
        for(Json::Value::ArrayIndex i = 0; i < jsonValue["handlers"].size(); i++) {
            handlers.push_back(handlerParser.fromJson(jsonValue["handlers"][i]));
        }

        return dometer::app::metrics::options{
            handlers
        };
    }
}
