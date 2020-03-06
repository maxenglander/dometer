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

    parser::parser(dometer::config::metrics::handler::parser handler_parser)
        : handler_parser(handler_parser) {}

    dometer::app::metrics::options parser::from_json(const Json::Value& json_value) const {
        assert(json_value.isMember("handlers"));
        assert(json_value["handlers"].isArray());

        std::vector<dometer::metrics::handler::options> handlers;
        for(Json::Value::ArrayIndex i = 0; i < json_value["handlers"].size(); i++) {
            handlers.push_back(handler_parser.from_json(json_value["handlers"][i]));
        }

        return dometer::app::metrics::options{
            handlers
        };
    }
}
