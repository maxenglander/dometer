#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "dometer/app/metrics/options.hpp"
#include "dometer/config/metrics/handler/parser.hpp"
#include "dometer/config/metrics/parser.hpp"
#include "dometer/metrics/handler/options.hpp"
#include "json/json.h"
#include "json/value.h"

namespace app = dometer::app;

namespace dometer::config::metrics {
    parser::parser()
        : parser::parser(dometer::config::metrics::handler::parser()) {}

    parser::parser(dometer::config::metrics::handler::parser handler_parser)
        : handler_parser(handler_parser) {}

    dometer::app::metrics::options parser::from_json(const Json::Value& json_value) const {
        std::map<std::string, std::string> additional_labels;
        if(json_value.isMember("additionalLabels")) {
            assert(json_value["additionalLabels"].isObject());
            for(auto it = json_value["additionalLabels"].begin(); it != json_value["additionalLabels"].end(); it++) {
                assert(it.key().isString());
                assert(it->isString());
                additional_labels.insert(std::pair<std::string, std::string>(
                    it.key().asString(), it->asString()
                ));
            }
        }

        assert(json_value.isMember("handlers"));
        assert(json_value["handlers"].isArray());

        std::vector<dometer::metrics::handler::options> handlers;
        for(Json::Value::ArrayIndex i = 0; i < json_value["handlers"].size(); i++) {
            handlers.push_back(handler_parser.from_json(json_value["handlers"][i]));
        }

        return dometer::app::metrics::options{
            additional_labels,
            handlers
        };
    }
}
