#include <cassert>

#include "dometer/config/metrics/handler/parser.hpp"
#include "dometer/metrics/handler/options.hpp"
#include "json/json.h"

namespace dometer::config::metrics::handler {
    parser::parser()
        : parser::parser(dometer::config::metrics::handler::prometheus::parser()) {}

    parser::parser(dometer::config::metrics::handler::prometheus::parser prometheus_parser)
        : prometheus_parser(prometheus_parser) {}

    dometer::metrics::handler::options parser::from_json(const Json::Value& json_value) const {
        assert(json_value.isMember("type"));
        assert(json_value["type"].isString());
        std::string type = json_value["type"].asString();
        
        if(type == "prometheus") {
            assert(json_value.isMember("prometheus"));
            assert(json_value["prometheus"].isObject());

            return prometheus_parser.from_json(json_value["prometheus"]);
        } else {
            assert(false);
        }
    }
}
