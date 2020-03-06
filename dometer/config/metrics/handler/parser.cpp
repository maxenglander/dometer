#include <cassert>

#include "dometer/config/metrics/handler/parser.hpp"
#include "dometer/metrics/handler/options.hpp"
#include "json/json.h"

namespace dometer::config::metrics::handler {
    parser::parser()
        : parser::parser(dometer::config::metrics::handler::prometheus::parser()) {}

    parser::parser(dometer::config::metrics::handler::prometheus::parser prometheus_parser)
        : prometheus_parser(prometheus_parser) {}

    dometer::metrics::handler::options parser::fromJson(const Json::Value& jsonValue) const {
        assert(jsonValue.isMember("type"));
        assert(jsonValue["type"].isString());
        std::string type = jsonValue["type"].asString();
        
        if(type == "prometheus") {
            assert(jsonValue.isMember("prometheus"));
            assert(jsonValue["prometheus"].isObject());

            return prometheus_parser.fromJson(jsonValue["prometheus"]);
        } else {
            assert(false);
        }
    }
}
